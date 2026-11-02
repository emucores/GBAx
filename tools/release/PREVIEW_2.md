# GBAx 2.0.0 Preview 2

This preview improves launcher data safety and makes save-state actions easier to understand.

- Launcher metadata, installed links and hidden-game lists now use atomic replacement. Failed writes report an error instead of silently replacing a file with partial data.
- Locate Missing Game repairs favourites, recent history and play statistics when a game moves. Select the same revision; save files remain in their original locations.
- Continue From State is distinguished from a normal Start Game. Configured state storage takes precedence over states beside the ROM.
- Quick Menu offers a selectable state slot (1–9), explicit save/load labels, operation feedback, save-file information and a shortcut to its folder.
- Quick Menu scrolls on smaller displays; the About dialog has a smaller minimum size.
- Copy Diagnostics provides version, OS and backend information without ROM paths or save contents.
- Settings labels distinguish launcher appearance from game display/audio and save storage.

## Downloads

- Windows 10/11 x64: extract the complete ZIP and run GBAx.exe. This preview is unsigned.
- Linux x86_64: Ubuntu 24.04 or a compatible glibc 2.39+ desktop. Make the AppImage executable before running it.
- macOS 15+: select arm64 for Apple Silicon or x86_64 for Intel. Files labelled unsigned are not notarized.
- Matching source, SHA-256 checksums, dependency notices and a download manifest accompany the packages.

## Validation and known limitations

Publication requires all four platform builds, the Linux automated suite and package runtime checks to pass. These checks do not replace real-device testing. Controller reconnect, sleep/wake, high-DPI/multiple-display behaviour and long gameplay sessions still need hardware validation. Preserve in-game saves and state backups before upgrading. State compatibility across core revisions is not guaranteed.

Automatic updates, FFmpeg recording, Lua scripting and Discord presence remain disabled in this portable release profile. No ROMs or proprietary BIOS files are bundled.

Report reproducible issues at https://github.com/emucores/GBAx/issues. Documentation and downloads: https://gbax-emulator.com.
