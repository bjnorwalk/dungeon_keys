#ifndef DUNGEON_SAVE_DATA_H
#define DUNGEON_SAVE_DATA_H

typedef struct {
    int highScore;
    int playerGold;
    int upgradeMaxHealth;
    float upgradeMoveSpeed;
    float upgradeEnemySlow;
    int upgradeComboBonus;
} SaveData;

void RestoreBrowserSave(void);
void LoadSaveData(SaveData *data);
void SaveSaveData(const SaveData *data);

#endif
