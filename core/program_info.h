#ifndef BACKENDS_P4TOOLS_MODULES_RTSMITH_CORE_PROGRAM_INFO_H_
#define BACKENDS_P4TOOLS_MODULES_RTSMITH_CORE_PROGRAM_INFO_H_

#include <functional>

#include "backends/p4tools/common/compiler/compiler_target.h"
#include "backends/p4tools/modules/rtsmith/core/config.h"
#include "control-plane/p4RuntimeSerializer.h"
#include "ir/ir.h"
#include "lib/castable.h"

namespace P4::P4Tools::RtSmith {

/// Stores target-specific information about a P4 program.
class ProgramInfo : public ICastable {
 private:
    /// The P4 program from which this object is derived.
    std::reference_wrapper<const CompilerResult> compilerResult;

    P4::P4RuntimeAPI p4runtimeApi;

 protected:
    explicit ProgramInfo(const CompilerResult &compilerResult, P4::P4RuntimeAPI p4runtimeApi);

    /// The `FuzzerConfig` object that stores the configurations of the fuzzer.
    /// Default values are provided in the `FuzzerConfig` class.
    P4::P4Tools::RtSmith::FuzzerConfig _fuzzerConfig = FuzzerConfig();

 public:
    ProgramInfo(const ProgramInfo &) = default;

    ProgramInfo(ProgramInfo &&) = default;

    ProgramInfo &operator=(const ProgramInfo &) = default;

    ProgramInfo &operator=(ProgramInfo &&) = default;

    ~ProgramInfo() override = default;

    /// @returns the P4 program associated with this program info.
    [[nodiscard]] const IR::P4Program *getProgram() const;

    /// @returns the P4RuntimeAPI associated with this program.
    [[nodiscard]] const P4::P4RuntimeAPI &getP4RuntimeApi() const;

    /// @returns the P4Info associated with this program.
    [[nodiscard]] const ::p4::config::v1::P4Info *getP4Info() const;

    /// @returns the FuzzerConfig associated with this program.
    [[nodiscard]] const FuzzerConfig &getFuzzerConfig() const;

    /// Proceeds to override the fuzzer configurations if a TOML file is provided (checked in either
    /// `Bmv2V1ModelRtSmithTarget` or `TofinoTnaRtSmithTarget`).
    void proceedToOverrideFuzzerConfigsViaFile(const char *path);

    /// Proceeds to override the fuzzer configurations if a string representation of the
    /// configurations of format TOML is provided (check in either `Bmv2V1ModelRtSmithTarget` or
    /// `TofinoTnaRtSmithTarget`).
    void proceedToOverrideFuzzerConfigsViaString(const char *configInString);
};

}  // namespace P4::P4Tools::RtSmith

#endif /* BACKENDS_P4TOOLS_MODULES_RTSMITH_CORE_PROGRAM_INFO_H_ */
