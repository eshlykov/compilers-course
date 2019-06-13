#include <utils/compiler.hpp>
#include <utils/file-utils.hpp>

#include <fstream>

void Compiler::Run() {
  AstBuildingPhase astBuilding(pathInputFile_);
  astBuilding.Run();
  astBuilding.PrintResults(JoinPath(pathOutputDir_, "ast"), ".gv");

  SymbolTableBuildingPhase symbolTableBuilding(astBuilding.GetAstRoot());
  symbolTableBuilding.Run();
  symbolTableBuilding.PrintResults(JoinPath(pathOutputDir_, "errors"), ".txt");

  if (!symbolTableBuilding.GetErrors()->empty()) {
    return;
  }

  TypeCheckingPhase typeChecking(astBuilding.GetAstRoot(),
                                 symbolTableBuilding.GetSymbolTable());
  typeChecking.Run();
  typeChecking.PrintResults(JoinPath(pathOutputDir_, "errors"), ".txt",
                            std::fstream::app);

  if (!typeChecking.GetErrors()->empty()) {
    return;
  }

  IrtBuildingPhase irtBuilding(astBuilding.GetAstRoot(),
                               symbolTableBuilding.GetSymbolTable());
  irtBuilding.Run();
  irtBuilding.PrintResults(pathOutputDir_, ".gv");

  IrtCanonizationPhase irtCanonization(irtBuilding.MethodTrees());
  irtCanonization.Run();
  irtCanonization.PrintResults(pathOutputDir_, ".gv");

  TraceFormationPhase traceFormation(irtCanonization.MethodTrees());
  traceFormation.Run();

  TilingFormationPhase tilingFormation(traceFormation.MethodTraces());
  tilingFormation.Run();

  AssemblyGenerationPhase assemblyGeneration(&tilingFormation.Commands());
  assemblyGeneration.Run();
  assemblyGeneration.PrintResults(JoinPath(pathOutputDir_, "code"), ".txt");
}
