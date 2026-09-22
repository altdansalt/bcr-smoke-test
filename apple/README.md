# apple: apple_support, rules_swift, rules_apple

Exercises (macOS + Xcode only; skipped on other hosts via `target_compatible_with`):

- `rules_swift`: `swift_library`, `swift_binary`, `swift_test` (XCTest)
- `rules_apple`: `macos_command_line_application` linking an Objective-C `main`
- `apple_support`: Objective-C compiled with the Apple `cc` toolchain (`objc_library` of a `.m` file)

All sources are original to this repo.
