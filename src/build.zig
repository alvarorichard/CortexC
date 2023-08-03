const Builder = @import("std").build.Builder;

pub fn build(b: *Builder) void {
    const target = b.standardTargetOptions(.{});
    const mode = b.optimization_default();

const lib = b.addSharedLibrary("function_parameter", "function_parameter.zig", .unversioned);
    lib.setBuildMode(mode);
    lib.setTarget(target);
    lib.install();
}