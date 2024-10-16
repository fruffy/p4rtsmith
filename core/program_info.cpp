#include "backends/p4tools/modules/rtsmith/core/program_info.h"

#include "backends/p4tools/common/compiler/compiler_target.h"

namespace P4::P4Tools::RtSmith {

ProgramInfo::ProgramInfo(const CompilerResult &compilerResult, P4::P4RuntimeAPI p4runtimeApi)
    : compilerResult(compilerResult), p4runtimeApi(p4runtimeApi) {}

/* =============================================================================================
 *  Getters
 * ============================================================================================= */

const IR::P4Program *ProgramInfo::getProgram() const { return &compilerResult.get().getProgram(); }

const P4::P4RuntimeAPI &ProgramInfo::getP4RuntimeApi() const { return p4runtimeApi; }

const ::p4::config::v1::P4Info *ProgramInfo::getP4Info() const { return p4runtimeApi.p4Info; }

const FuzzerConfig &ProgramInfo::getFuzzerConfig() const { return _fuzzerConfig; }

void ProgramInfo::proceedToOverrideFuzzerConfigsViaFile(const char *path) {
    _fuzzerConfig.overrideFuzzerConfigsViaFile(path);
}

void ProgramInfo::proceedToOverrideFuzzerConfigsViaString(const char *configInString) {
    _fuzzerConfig.overrideFuzzerConfigsViaString(configInString);
}

}  // namespace P4::P4Tools::RtSmith
