#include <utils/compilation-phase.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <utils/file-utils.hpp>

#include <ast/visitor/dot-lang-visitor.hpp>
#include <ast/visitor/generate-code-visitor.hpp>
#include <ast/visitor/irt-builder-visitor.hpp>
#include <ast/visitor/symbol-table-builder-visitor.hpp>
#include <ast/visitor/type-checker-visitor.hpp>

#include <irt/visitor/dot-lang-visitor.hpp>
#include <irt/visitor/double-call-elimination-visitor.hpp>
#include <irt/visitor/eseq-elimination-visitor.hpp>
#include <irt/visitor/seq-linearizer-visitor.hpp>
#include <irt/visitor/trace-formation-visitor.hpp>

#include <cg/node/commands.hpp>
#include <cg/trace/trace.hpp>
#include <cg/visitor/command-emitter-visitor.hpp>
#include <cg/visitor/dot-lang-visitor.hpp>
#include <cg/visitor/tiling-visitor.hpp>

#include <utils/bison-parser.hpp>

void AstBuildingPhase::Run() {
  BisonParser parser(pathInputFile_);
  astRoot_ =
      std::unique_ptr<const Ast::Program>(parser.BuildAst(pathInputFile_));
}

void AstBuildingPhase::PrintResults(const std::string& pathOutputFile,
                                    const std::string& extension,
                                    const std::ios_base::openmode& openMode) {
  std::fstream outputStream(pathOutputFile + extension, openMode);
  outputStream << ToDotLanguage() << std::endl;
  outputStream.close();
}

void AstBuildingPhase::PrintCodeGenerated(
    const std::string& pathOutputFile, const std::string& extension,
    const std::ios_base::openmode& openMode) {
  std::fstream outputStream(pathOutputFile + extension, openMode);
  outputStream << ToCode() << std::endl;
  outputStream.close();
}

const Ast::Program* AstBuildingPhase::GetAstRoot() const {
  return astRoot_.get();
}

std::string AstBuildingPhase::ToDotLanguage() {
  assert(astRoot_);
  if (dotLangTraversal_.empty()) {
    Ast::DotLangVisitor dotLangVisitor(verbose_ > 1);
    astRoot_->Accept(&dotLangVisitor);
    dotLangTraversal_ = dotLangVisitor.GetTraversalInDotLanguage();
  }
  return dotLangTraversal_;
}

std::string AstBuildingPhase::ToCode() {
  assert(astRoot_);
  if (codeGenerated_.empty()) {
    Ast::GenerateCodeVisitor generateCodeVisitor(verbose_ > 1);
    astRoot_->Accept(&generateCodeVisitor);
    codeGenerated_ = generateCodeVisitor.GetCode();
  }
  return codeGenerated_;
}

void SymbolTableBuildingPhase::Run() {
  Ast::SymbolTableBuilderVisitor symbolTableBuilderVisitor(verbose_ > 1);
  symbolTableBuilderVisitor.Visit(astRoot_);
  symbolTable_ = std::unique_ptr<const SymbolTable>(
      symbolTableBuilderVisitor.GetSymbolTable());
  errors_ = std::unique_ptr<const std::vector<CompilationError>>(
      symbolTableBuilderVisitor.Errors());
}

void SymbolTableBuildingPhase::PrintResults(
    const std::string& pathOutputFile, const std::string& extension,
    const std::ios_base::openmode& openMode) {
  assert(errors_);
  if (!errors_->empty()) {
    for (auto it = errors_->begin(); it != errors_->end(); ++it) {
      std::cout << it->ToString() << std::endl;
    }
  }
}

const SymbolTable* SymbolTableBuildingPhase::GetSymbolTable() const {
  assert(symbolTable_);
  return symbolTable_.get();
}

const std::vector<CompilationError>* SymbolTableBuildingPhase::GetErrors()
    const {
  assert(errors_);
  return errors_.get();
}

void TypeCheckingPhase::Run() {
  Ast::TypeCheckerVisitor typeCheckerVisitor(symbolTable_, verbose_ > 1);
  typeCheckerVisitor.Visit(astRoot_);
  errors_ = std::unique_ptr<const std::vector<CompilationError>>(
      typeCheckerVisitor.GetErrors());
}

void TypeCheckingPhase::PrintResults(const std::string& pathOutputFile,
                                     const std::string& extension,
                                     const std::ios_base::openmode& openMode) {
  assert(errors_);
  if (!errors_->empty()) {
    for (auto it = errors_->begin(); it != errors_->end(); ++it) {
      std::cout << it->ToString() << std::endl;
    }
  }
}

const std::vector<CompilationError>* TypeCheckingPhase::GetErrors() const {
  assert(errors_);
  return errors_.get();
}

using MethodToIrtMap =
    std::unordered_map<std::string, std::unique_ptr<const Irt::Statement>>;

void IrtBuildingPhase::Run() {
  Ast::IrtBuilderVisitor irtBuilderVisitor(symbolTable_, verbose_ > 1);
  irtBuilderVisitor.Visit(astRoot_);
  methodTrees_ = std::move(irtBuilderVisitor.MethodTrees());
}

void IrtBuildingPhase::PrintResults(const std::string& pathOutputFile,
                                    const std::string& extension,
                                    const std::ios_base::openmode& openMode) {
  const MethodToIrtMap* methodTreesPtr = MethodTrees();
  for (auto it = methodTreesPtr->begin(); it != methodTreesPtr->end(); ++it) {
    const std::string& methodName = it->first;
    std::string dirPath = JoinPath(pathOutputFile, methodName);
    CreateDirectory(dirPath);

    std::fstream outputStream(JoinPath(dirPath, "irt" + extension), openMode);
    outputStream << ToDotLanguage(methodName) << std::endl;
    outputStream.close();
  }
}

const MethodToIrtMap* IrtBuildingPhase::MethodTrees() const {
  assert(methodTrees_);
  return methodTrees_.get();
}

std::string IrtBuildingPhase::ToDotLanguage(const std::string& methodName) {
  assert(methodTrees_);
  Irt::DotLangVisitor dotLangVisitor(verbose_ > 1);
  methodTrees_->at(methodName)->Accept(&dotLangVisitor);
  return dotLangVisitor.GetTraversalInDotLanguage();
}

void IrtCanonizationPhase::Run() {
  for (auto it = methodTrees_->begin(); it != methodTrees_->end(); ++it) {
    Irt::DoubleCallEliminationVisitor callEliminationVisitor(verbose_ > 1);
    it->second->Accept(&callEliminationVisitor);
    auto res = methodTreesWithoutDoubleCalls_->emplace(
        it->first, std::move(callEliminationVisitor.ResultTree()));

    Irt::EseqEliminationVisitor eseqEliminationVisitor(verbose_ > 1);
    res.first->second->Accept(&eseqEliminationVisitor);
    auto res2 = methodTreesWithoutEseqs_->emplace(
        it->first, std::move(eseqEliminationVisitor.ResultTree()));

    Irt::SeqLinearizerVisitor seqLinearizerVisitor(verbose_ > 1);
    res2.first->second->Accept(&seqLinearizerVisitor);
    methodTreesLinearized_->emplace(
        it->first, std::move(seqLinearizerVisitor.ResultTree()));
  }
}

void IrtCanonizationPhase::PrintResults(
    const std::string& pathOutputFile, const std::string& extension,
    const std::ios_base::openmode& openMode) {
  if (verbose_ > 0) {
    assert(methodTreesWithoutDoubleCalls_);
    for (auto it = methodTreesWithoutDoubleCalls_->begin();
         it != methodTreesWithoutDoubleCalls_->end(); ++it) {
      const std::string& methodName = it->first;
      std::string dirPath = JoinPath(pathOutputFile, methodName);
      CreateDirectory(dirPath);

      std::fstream outputStream(JoinPath(dirPath, "irtCanon1" + extension),
                                openMode);
      outputStream << ToDotLanguage(methodTreesWithoutDoubleCalls_.get(),
                                    methodName)
                   << std::endl;
      outputStream.close();
    }

    assert(methodTreesWithoutEseqs_);
    for (auto it = methodTreesWithoutEseqs_->begin();
         it != methodTreesWithoutEseqs_->end(); ++it) {
      const std::string& methodName = it->first;
      std::string dirPath = JoinPath(pathOutputFile, methodName);
      CreateDirectory(dirPath);

      std::fstream outputStream(JoinPath(dirPath, "irtCanon2" + extension),
                                openMode);
      outputStream << ToDotLanguage(methodTreesWithoutEseqs_.get(), methodName)
                   << std::endl;
      outputStream.close();
    }
  }

  assert(methodTreesLinearized_);
  for (auto it = methodTreesLinearized_->begin();
       it != methodTreesLinearized_->end(); ++it) {
    const std::string& methodName = it->first;
    std::string dirPath = JoinPath(pathOutputFile, methodName);
    CreateDirectory(dirPath);

    std::fstream outputStream(JoinPath(dirPath, "irtCanon" + extension),
                              openMode);
    outputStream << ToDotLanguage(methodTreesLinearized_.get(), methodName)
                 << std::endl;
    outputStream.close();
  }
}

const MethodToIrtMap* IrtCanonizationPhase::MethodTrees() const {
  assert(methodTreesLinearized_);
  return methodTreesLinearized_.get();
}

std::string IrtCanonizationPhase::ToDotLanguage(
    const MethodToIrtMap* methodTreesMap, const std::string& methodName) {
  assert(methodTreesMap);
  Irt::DotLangVisitor dotLangVisitor(verbose_ > 1);
  methodTreesMap->at(methodName)->Accept(&dotLangVisitor);
  return dotLangVisitor.GetTraversalInDotLanguage();
}

void TraceFormationPhase::Run() {
  for (auto it = methodTrees_->begin(); it != methodTrees_->end(); ++it) {
    Irt::TraceFormationVisitor traceVisitor(verbose_ > 1);
    it->second->Accept(&traceVisitor);

    std::unique_ptr<Cg::Trace> trace = traceVisitor.Trace();
    trace = Cg::RearrangeBlocks(std::move(trace));
    std::unique_ptr<Cg::Trace> traceConst(trace.release());

    methodTraces_->emplace(it->first, std::move(traceConst));
  }
}

void TraceFormationPhase::PrintResults(
    const std::string& pathOutputFile, const std::string& extension,
    const std::ios_base::openmode& openMode) {
  assert(methodTraces_);
  for (auto traceIt = methodTraces_->begin(); traceIt != methodTraces_->end();
       ++traceIt) {
    const std::string& methodName = traceIt->first;
    std::string dirPath =
        JoinPath(JoinPath(pathOutputFile, methodName), "blocks");
    CreateDirectory(dirPath);

    int i = 0;
    for (auto blockIt = traceIt->second->begin();
         blockIt != traceIt->second->end(); ++blockIt, ++i) {
      std::fstream outputStream(
          JoinPath(dirPath, std::to_string(i) + extension), openMode);
      outputStream << ToDotLanguage(blockIt->get()) << std::endl;
      outputStream.close();
    }
  }
}

const MethodToTraceMap* TraceFormationPhase::MethodTraces() const {
  assert(methodTraces_);
  return methodTraces_.get();
}

std::string TraceFormationPhase::ToDotLanguage(const Cg::Block* block) {
  assert(block);
  Irt::DotLangVisitor dotLangVisitor(verbose_ > 1);
  block->Accept(&dotLangVisitor);
  return dotLangVisitor.GetTraversalInDotLanguage();
}

void TilingFormationPhase::Run() {
  for (auto trace = methodTraces_->begin(); trace != methodTraces_->end();
       ++trace) {
    auto value = trace->second.get();
    for (auto block = value->begin(); block != value->end(); ++block) {
      for (const auto& statement : (*block)->Statements()) {
        Cg::TilingVisitor* tilingVisitor =
            new Cg::TilingVisitor(statement.get(), verbose_ > 1);
        statement->Accept(tilingVisitor);
        commands_[trace->first].emplace_back(tilingVisitor);
      }
    }
  }
}

std::string TilingFormationPhase::ToDotLanguage(const Cg::Command* tree) {
  assert(tree);
  Cg::DotLangVisitor dotLangVisitor(verbose_ > 1);
  tree->Accept(&dotLangVisitor);
  return dotLangVisitor.GetTraversalInDotLanguage();
}

void TilingFormationPhase::PrintResults(
    const std::string& pathOutputFile, const std::string& extension,
    const std::ios_base::openmode& openMode) {
  for (auto methodIt = commands_.begin(); methodIt != commands_.end();
       ++methodIt) {
    const std::string& methodName = methodIt->first;
    std::string dirPath =
        JoinPath(JoinPath(pathOutputFile, methodName), "commands");
    CreateDirectory(dirPath);

    int visitorIndex = 0;
    for (auto visitorIt = methodIt->second.begin();
         visitorIt != methodIt->second.end(); ++visitorIt, ++visitorIndex) {
      const Cg::Command* command = (*visitorIt)->Result();
      std::fstream outputStream(
          JoinPath(dirPath, std::to_string(visitorIndex) + extension),
          openMode);
      outputStream << ToDotLanguage(command) << std::endl;
      outputStream.close();
    }
  }
}

const MethodToCommandsList& TilingFormationPhase::Commands() const {
  return commands_;
}

void AssemblyGenerationPhase::Run() {
  for (auto methodIt = commands_->begin(); methodIt != commands_->end();
       ++methodIt) {
    for (auto visitorIt = methodIt->second.begin();
         visitorIt != methodIt->second.end(); ++visitorIt) {
      Cg::CommandEmitterVisitor commandEmitter(verbose_ > 1);
      (*visitorIt)->Result()->Accept(&commandEmitter);
      for (const auto& line : commandEmitter.Result()) {
        std::stringstream builder;
        builder << line.Text();
        codes_.push_back(builder.str());
      }
    }
  }
}

void AssemblyGenerationPhase::PrintResults(
    const std::string& pathOutputFile, const std::string& extension,
    const std::ios_base::openmode& openMode) {
  std::fstream outputStream(pathOutputFile + extension, openMode);
  for (const auto& line : codes_) {
    outputStream << line << std::endl;
  }
}
