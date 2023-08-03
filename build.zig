const Builder = @import("std").build.Builder;

pub fn build(b: *Builder) void {
    const target = b.standardTargetOptions(.{});
    const mode = b.standardReleaseOptions(); //-Drelease-safe|release-fast|release-small

    const lib = b.addSharedLibrary("function_parameter", "src/function_parameter.zig", .unversioned);
    lib.setBuildMode(mode);
    lib.setTarget(target);
    lib.linkLibC(); // next function need libc
    lib.install();

    const exe = b.addExecutable("CortexC", null);
    exe.addCSourceFile("src/main.c", &.{
        "-Wall",
        "-Wextra",
        // "-Werror",
    });
    exe.setBuildMode(mode);
    exe.setTarget(target);
    exe.addIncludePath("src");
    exe.linkLibrary(lib);
    exe.linkLibC();
    exe.install();

    const run_cmd = exe.run();
    run_cmd.step.dependOn(b.getInstallStep());
    if (b.args) |args| {
        run_cmd.addArgs(args);
    }

    // zig build run - running Exe.
    const run_step = b.step("run", b.fmt("Run the {s} app.", .{exe.name}));
    run_step.dependOn(&run_cmd.step);
}
