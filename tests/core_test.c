#include "../src/save_data.h"
#include "../src/word_bank.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    /* Run in a disposable directory, never alongside a player's save. */
    SaveData expected = {123, 40, 2, 0.9f, 1.1f, 3};
    SaveData actual = {0, 0, 0, 1.0f, 1.0f, 0};
    LoadSaveData(&actual);
    assert(actual.highScore == 0 && actual.upgradeMoveSpeed == 1.0f);
    SaveSaveData(&expected);
    FILE *file = fopen("save.dat", "r");
    assert(file);
    char line[128];
    assert(fgets(line, sizeof(line), file));
    fclose(file);
    assert(strcmp(line, "123 40 2 0.900 1.100 3\n") == 0);
    LoadSaveData(&actual);
    assert(actual.highScore == 123 && actual.playerGold == 40);
    assert(actual.upgradeMaxHealth == 2 && actual.upgradeComboBonus == 3);
    assert(fabsf(actual.upgradeMoveSpeed - 0.9f) < 0.0001f);
    assert(fabsf(actual.upgradeEnemySlow - 1.1f) < 0.0001f);
    file = fopen("save.dat", "w");
    assert(file);
    fputs("999 888 broken", file);
    fclose(file);
    LoadSaveData(&actual);
    assert(actual.highScore == 123 && actual.playerGold == 40);
    assert(actual.upgradeMaxHealth == 2 && actual.upgradeComboBonus == 3);
    remove("save.dat");

    srand(42);
    InitWordBank();
    LoadExternalWords(); /* Missing optional word list is harmless. */
    for (int difficulty = 1; difficulty <= 3; difficulty++) {
        for (int wave = 1; wave <= 10; wave++) {
            const char *word = GetRandomWordForWave(wave, difficulty);
            assert(word && strlen(word) > 0 && strlen(word) < 32);
        }
    }
    file = fopen("wordlist.txt", "w");
    assert(file);
    fputs("# ignored\n\nabcdefghijklmnopqrstuvwxyzzzzzzzzzzzzzzzzzz\n", file);
    fclose(file);
    LoadExternalWords();
    for (int i = 0; i < 100; i++) {
        const char *word = GetRandomLongWord();
        assert(word && strlen(word) > 0 && strlen(word) < 32);
    }
    remove("wordlist.txt");
    puts("core regression checks passed");
    return 0;
}
