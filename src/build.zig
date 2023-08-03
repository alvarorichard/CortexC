const Builder = @import("std").build.Builder;

pub fn build(b: *Builder) void {
    const target = b.standardTargetOptions(.{});
    const mode = b.optimization_default();

    const exe = b.addSharedLibrary("function_parameter", "function_parameter.zig");
    exe.setBuildMode(mode);
    exe.setTarget(target);
    exe.install();
}
