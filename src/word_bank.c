#include "word_bank.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_BANK 600
static char wordBank[MAX_WORD_BANK][32];
static int wordCount = 0;

// Initialise the base word list used for enemies and items.  Feel free to
// extend this list; additional words can also be loaded from an external
// wordlist.txt file via LoadExternalWords().
void InitWordBank(void) {
    const char *baseWords[] = {
        // Easy words
        "cat", "map", "run", "gold", "dark", "door", "loot", "fire",
        "spell", "sword", "ghost", "crypt", "arrow", "torch", "key", "lock",
        "orc", "elf", "kobold", "coin", "pit", "trap",
        // Medium words
        "python", "typing", "wizard", "dungeon", "monster", "shadow",
        "potion", "skeleton", "treasure", "portal", "castle", "dagger",
        "forest", "scroll", "magic", "keyboard", "adventure", "explore",
        // Harder words
        "roguelike", "labyrinth", "necromancer", "basilisk", "sorcerer",
        "enchantment", "catacombs", "rhapsody", "phantasm", "ethereal"
    };
    int count = sizeof(baseWords) / sizeof(baseWords[0]);
    for (int i = 0; i < count && wordCount < MAX_WORD_BANK; i++) {
        strncpy(wordBank[wordCount], baseWords[i], sizeof(wordBank[wordCount]) - 1);
        wordBank[wordCount][sizeof(wordBank[wordCount]) - 1] = '\0';
        wordCount++;
    }
}

// Load additional words from wordlist.txt, one per line.  Words longer than
// 31 characters are truncated.  Lines beginning with # are treated as
// comments.
void LoadExternalWords(void) {
    FILE *file = fopen("wordlist.txt", "r");
    if (!file) return;
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), file) && wordCount < MAX_WORD_BANK) {
        // Skip comments and empty lines
        if (buffer[0] == '#' || buffer[0] == '\n' || buffer[0] == '\0') continue;
        // Strip newline
        size_t len = strlen(buffer);
        if (buffer[len - 1] == '\n') buffer[len - 1] = '\0';
        // Copy word
        strncpy(wordBank[wordCount], buffer, sizeof(wordBank[wordCount]) - 1);
        wordBank[wordCount][sizeof(wordBank[wordCount]) - 1] = '\0';
        wordCount++;
    }
    fclose(file);
}

// Retrieve a random word appropriate for the current wave.  Earlier waves
// favour shorter words, while later waves may include longer ones.
const char *GetRandomWordForWave(int wave, int difficulty) {
    // Adjust the effective wave based on difficulty.  Easier difficulty
    // reduces the wave level so shorter words remain available longer;
    // harder difficulty increases it so longer words appear sooner.
    int effectiveWave = wave;
    if (difficulty == 1 && effectiveWave > 1) effectiveWave--;
    else if (difficulty == 3) effectiveWave++;
    int attempts = 0;
    while (attempts < 40) {
        int index = rand() % wordCount;
        const char *w = wordBank[index];
        size_t len = strlen(w);
        if (effectiveWave < 3) {
            if (len <= 5) return w;
        } else if (effectiveWave < 6) {
            if (len <= 8) return w;
        } else {
            if (len > 4) return w;
        }
        attempts++;
    }
    return wordBank[rand() % wordCount];
}

// Retrieve a random longer word for boss battles.  Chooses from words with
// length >= 8.  If none available, returns a random word.
const char *GetRandomLongWord(void) {
    int attempts = 0;
    while (attempts < 50) {
        int index = rand() % wordCount;
        const char *w = wordBank[index];
        if (strlen(w) >= 8) return w;
        attempts++;
    }
    return wordBank[rand() % wordCount];
}

