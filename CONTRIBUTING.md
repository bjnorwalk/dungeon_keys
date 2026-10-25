# Contributing

Start from the current `main` branch and use a short-lived branch named for one change. Keep refactors, behavior changes, and dependency updates in separate commits; do not rewrite published history.

Before opening a PR, review the diff for generated files, credentials, unrelated changes, and storage-format compatibility. Keep lockfiles and intentional fixtures; exclude local data and build output. Explain the reason for the change, the checks actually run, remaining limits, and rollback. Identify self-review honestly; automated checks are not independent review.

## Validation

Follow the native and Emscripten build instructions in [README.md](README.md). Require both native `compile` and browser `build` checks. Run persistence/word-bank tests in a disposable directory because they create save.dat and wordlist.txt. Build success does not verify keyboard feel, combat, or real-browser persistence; report those manual checks separately. Preserve the six-field save format and browser storage key.

## Merge and maintenance

Merge only after required checks pass and review conversations are resolved. Prefer squash for a short branch containing work-in-progress commits; retain useful commit history where it explains the change. Delete a merged branch only after checking that no open PR depends on it. Use a revert PR for rollback and update the README when setup or architecture changes.

