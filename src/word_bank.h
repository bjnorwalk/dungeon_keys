#ifndef DUNGEON_WORD_BANK_H
#define DUNGEON_WORD_BANK_H

void InitWordBank(void);
void LoadExternalWords(void);
const char *GetRandomWordForWave(int wave, int difficulty);
const char *GetRandomLongWord(void);

#endif
