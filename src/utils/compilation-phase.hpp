#pragma once

#include <fstream>
#include <memory>
#include <string>

#include <ast/node/program.hpp>
#include <ast/visitor/symbol-table.hpp>
#include <cg/trace/trace.hpp>
#include <cg/visitor/tiling-visitor.hpp>
#include <irt/node/statement.hpp>
#include <utils/compilation-error.hpp>

class CompilationPhase {
 public:
  explicit CompilationPhase(int verbose = 0) : verbose_(verbose) {}
  virtual ~CompilationPhase() = default;

  virtual void Run() = 0;
  virtual void PrintResults(
      const std::string& pathOutputFile, const std::string& extension,
      const std::ios_base::openmode& openMode = std::fstream::out) = 0;

 protected:
  int verbose_;
};

class AstBuildingPhase : public CompilationPhase {
 public:
  explicit AstBuildingPhase(std::string pathInputFile, int verbose = 0)
      : CompilationPhase(verbose), pathInputFile_(std::move(pathInputFile)) {}

  void Run() override;
  void PrintResults(
      const std::string& pathOutputFile, const std::string& extension,
      const std::ios_base::openmode& openMode = std::fstream::out) override;

  void PrintCodeGenerated(
      const std::string& pathOutputFile, const std::string& extension,
      const std::ios_base::openmode& openMode = std::fstream::out);

  const Ast::Program* GetAstRoot() const;
  std::string ToDotLanguage();
  std::string ToCode();

 private:
  // parameters
  std::string pathInputFile_;

  // results
  std::unique_ptr<const Ast::Program> astRoot_;
  std::string dotLangTraversal_;
  std::string codeGenerated_;
};

class SymbolTableBuildingPhase : public CompilationPhase {
 public:
  explicit SymbolTableBuildingPhase(const Ast::Program* astRoot,
                                    int verbose = 0)
      : CompilationPhase(verbose), astRoot_(astRoot) {}

  void Run() override;
  void PrintResults(
      const std::string& pathOutputFile, const std::string& extension,
      const std::ios_base::openmode& openMode = std::fstream::out) override;

  const SymbolTable* GetSymbolTable() const;
  const std::vector<CompilationError>* GetErrors() const;

 private:
  // parameters
  const Ast::Program* astRoot_;

  // results
  std::unique_ptr<const SymbolTable> symbolTable_;
  std::unique_ptr<const std::vector<CompilationError>> errors_;
};

class TypeCheckingPhase : public CompilationPhase {
 public:
  TypeCheckingPhase(const Ast::Program* astRoot, const SymbolTable* symbolTable,
                    int verbose = 0)
      : CompilationPhase(verbose),
        astRoot_(astRoot),
        symbolTable_(symbolTable) {}

  void Run() override;
  void PrintResults(
      const std::string& pathOutputFile, const std::string& extension,
      const std::ios_base::openmode& openMode = std::fstream::out) override;

  const std::vector<CompilationError>* GetErrors() const;

 private:
  // parameters
  const Ast::Program* astRoot_;
  const SymbolTable* symbolTable_;

  // results
  std::unique_ptr<const std::vector<CompilationError>> errors_;
};

using MethodToIrtMap =
    std::unordered_map<std::string, std::unique_ptr<const Irt::Statement>>;

class IrtBuildingPhase : public CompilationPhase {
 public:
  IrtBuildingPhase(const Ast::Program* astRoot, const SymbolTable* symbolTable,
                   int verbose = 0)
      : CompilationPhase(verbose),
        astRoot_(astRoot),
        symbolTable_(symbolTable) {}

  void Run() override;
  void PrintResults(
      const std::string& pathOutputFile, const std::string& extension,
      const std::ios_base::openmode& openMode = std::fstream::out) override;

  const MethodToIrtMap* MethodTrees() const;

  std::string ToDotLanguage(const std::string& methodName);

 private:
  // parameters
  const Ast::Program* astRoot_;
  const SymbolTable* symbolTable_;

  // results
  std::unique_ptr<const MethodToIrtMap> methodTrees_;
};

class IrtCanonizationPhase : public CompilationPhase {
 public:
  explicit IrtCanonizationPhase(const MethodToIrtMap* methodTrees,
                                int verbose = 0)
      : CompilationPhase(verbose),
        methodTrees_(methodTrees),
        methodTreesWithoutDoubleCalls_(new MethodToIrtMap()),
        methodTreesWithoutEseqs_(new MethodToIrtMap()),
        methodTreesLinearized_(new MethodToIrtMap()) {}

  void Run() override;
  void PrintResults(
      const std::string& pathOutputFile, const std::string& extension,
      const std::ios_base::openmode& openMode = std::fstream::out) override;

  const MethodToIrtMap* MethodTrees() const;

  std::string ToDotLanguage(const MethodToIrtMap* methodTreesMap,
                            const std::string& methodName);

 private:
  // parameters
  const MethodToIrtMap* methodTrees_;

  // results
  std::unique_ptr<MethodToIrtMap> methodTreesWithoutDoubleCalls_;
  std::unique_ptr<MethodToIrtMap> methodTreesWithoutEseqs_;
  std::unique_ptr<MethodToIrtMap> methodTreesLinearized_;
};

using MethodToTraceMap =
    std::unordered_map<std::string, std::unique_ptr<const Cg::Trace>>;

class TraceFormationPhase : public CompilationPhase {
 public:
  explicit TraceFormationPhase(const MethodToIrtMap* methodTrees,
                               int verbose = 0)
      : CompilationPhase(verbose),
        methodTrees_(methodTrees),
        methodTraces_(new MethodToTraceMap()) {}

  void Run() override;
  void PrintResults(
      const std::string& pathOutputFile, const std::string& extension,
      const std::ios_base::openmode& openMode = std::fstream::out) override;

  const MethodToTraceMap* MethodTraces() const;

  std::string ToDotLanguage(const Cg::Block* block);

 private:
  // parameters
  const MethodToIrtMap* methodTrees_;

  // results
  std::unique_ptr<MethodToTraceMap> methodTraces_;
};

using MethodToCommandsList =
    std::unordered_map<std::string,
                       std::vector<std::unique_ptr<const Cg::TilingVisitor>>>;

class TilingFormationPhase : public CompilationPhase {
 public:
  explicit TilingFormationPhase(const MethodToTraceMap* methodTraces,
                                int verbose = 0)
      : CompilationPhase(verbose), methodTraces_(methodTraces) {}

  void Run() override;
  void PrintResults(
      const std::string& pathOutputFile, const std::string& extension,
      const std::ios_base::openmode& openMode = std::fstream::out) override;

  const MethodToCommandsList& Commands() const;
  std::string ToDotLanguage(const Cg::Command* tree);

 private:
  const MethodToTraceMap* methodTraces_;

  MethodToCommandsList commands_;
};

class AssemblyGenerationPhase : public CompilationPhase {
 public:
  explicit AssemblyGenerationPhase(const MethodToCommandsList* commands,
                                   int verbose = 0)
      : CompilationPhase(verbose), commands_(commands) {}

  void Run() override;
  void PrintResults(
      const std::string& pathOutputFile, const std::string& extension,
      const std::ios_base::openmode& openMode = std::fstream::out) override;

 private:
  const MethodToCommandsList* commands_;

  std::vector<std::string> codes_;
};
