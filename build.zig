const Builder = @import("std").Build;

pub fn build(b: *Builder) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const lib = b.addSharedLibrary(.{
        .name = "function_parameter",
        .target = target,
        .optimize = optimize,
        .root_source_file = .{ .path = "src/function_parameter.zig" },
    });
    lib.linkLibC(); // next function need libc

    b.installArtifact(lib);

    const exe = b.addExecutable(.{
        .name = "CortexC",
        .target = target,
        .optimize = optimize,
    });
    exe.addCSourceFile(.{
        .file = .{ .path = "src/main.c" },
        .flags = &.{
            "-Wall",
            "-Wextra",
            "-Wpedantic",
            "-Wshadow",
        },
    });
    exe.omit_frame_pointer = false;
    exe.addIncludePath(.{ .path = "src" });
    exe.linkLibrary(lib);
    exe.linkLibC();

    b.installArtifact(exe);

    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());
    if (b.args) |args| {
        run_cmd.addArgs(args);
    }

    // zig build run - running Exe.
    const run_step = b.step("run", b.fmt("Run the {s} app.", .{exe.name}));
    run_step.dependOn(&run_cmd.step);
}
