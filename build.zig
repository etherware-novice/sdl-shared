const std = @import("std");
const asset_path = "assets/";
const compile_args = .{
    "-Wall",
    "-Wextra",
    "-Wpedantic",
    "-O2",
    "-DASSET_PATH=\"" ++ asset_path ++ "\"",
};

pub fn build(b: *std.Build) !void {
    const target = b.standardTargetOptions(.{});

    // Standard release options allow the person running `zig build` to select
    // between Debug, ReleaseSafe, ReleaseFast, and ReleaseSmall.
    const mode = b.standardOptimizeOption(.{});

    // create your executable
    const exe = b.addExecutable(.{
        .name = "tester",
        .optimize = mode,
        .target = target,
    });
    exe.addIncludePath(.{ .path = "include" });
    exe.linkLibC();
    exe.linkSystemLibrary("SDL2");

    exe.addCSourceFiles(
        &.{
            "src/main.c",
        },
        &compile_args,
    );

    const mylib = b.addStaticLibrary(.{
        .name = "SDLShare",
        .optimize = mode,
        .target = target,
    });
    mylib.addIncludePath(.{ .path = "include" });
    mylib.linkLibC();
    exe.linkSystemLibrary("SDL2");
    exe.linkLibrary(mylib);

    mylib.addCSourceFiles(
        &.{
            "src/create.c",
            "src/init.c",
            "src/input.c",
            "src/query.c",
        },
        &compile_args,
    );

    b.installArtifact(exe);
    b.installArtifact(mylib);
    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());
    const run_step = b.step("run", "Run the app");
    run_step.dependOn(&run_cmd.step);
}
