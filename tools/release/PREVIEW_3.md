# GBAx 2.0.0 Preview 3

Fixes missing launcher artwork and clipped game titles when resizing or maximizing the window.

- Artwork uses Libretro’s GitHub repository first, with the thumbnail server as fallback.
- A cached filename index matches regional cover filenames without per-game GitHub API searches.
- Existing covers remain cached. Previous failed-download cooldowns are reset for the new sources; new failures retain bounded retries and cooldowns.
- Grid covers and titles have separate drawing areas and font-aware row heights. Long titles use an ellipsis and a full-title tooltip.

Downloads: Windows x64 ZIP, Linux x86_64 AppImage, macOS Apple Silicon and Intel DMGs, source ZIP and SHA256 checksums. Mac and Windows builds are unsigned. This is a preview release.

Extract the Windows ZIP into a new folder and launch GBAx.exe. Existing user data and saves remain in place. If automatic artwork is disabled, use Settings → Download Missing Artwork.
