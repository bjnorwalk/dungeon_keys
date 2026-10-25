#include "save_data.h"
#include <stdio.h>
#ifdef PLATFORM_WEB
#include <emscripten/emscripten.h>
#endif

void RestoreBrowserSave(void) {
#ifdef PLATFORM_WEB
    // Browser storage keeps the existing save format without a server.
    EM_ASM({
        try {
            const saved = localStorage.getItem('dungeonKeys.save');
            if (saved) FS.writeFile('save.dat', saved);
        } catch (_) { /* Storage may be unavailable in private browsing. */ }
    });
#endif
}

// Load save data from save.dat.  The file stores high score, gold and
// upgrade levels.  If not present or malformed, defaults are used.
void LoadSaveData(SaveData *data) {
    FILE *file = fopen("save.dat", "r");
    if (!file) return;
    int hs = 0;
    int gold = 0;
    int maxH = 0;
    float moveUp = 1.0f;
    float slowUp = 1.0f;
    int comboUp = 0;
    if (fscanf(file, "%d %d %d %f %f %d", &hs, &gold, &maxH, &moveUp, &slowUp, &comboUp) == 6) {
        data->highScore = hs;
        data->playerGold = gold;
        data->upgradeMaxHealth = maxH;
        data->upgradeMoveSpeed = moveUp;
        data->upgradeEnemySlow = slowUp;
        data->upgradeComboBonus = comboUp;
    }
    fclose(file);
}

// Save save data to save.dat.  Called whenever upgrades change or a new high
// score is achieved.
void SaveSaveData(const SaveData *data) {
    FILE *file = fopen("save.dat", "w");
    if (!file) return;
    fprintf(file, "%d %d %d %.3f %.3f %d\n", data->highScore, data->playerGold, data->upgradeMaxHealth,
            data->upgradeMoveSpeed, data->upgradeEnemySlow, data->upgradeComboBonus);
    fclose(file);
#ifdef PLATFORM_WEB
    EM_ASM({
        try {
            localStorage.setItem('dungeonKeys.save', FS.readFile('save.dat', { encoding: 'utf8' }));
        } catch (_) { /* The run remains playable without persistent storage. */ }
    });
#endif
}

