#include "tree.h"

GenreNode* createGenreNode(const char* name) {
    GenreNode* node = (GenreNode*)malloc(sizeof(GenreNode));
    strcpy(node->genreName, name);
    node->fs = node->nb = node->pr = NULL;
    node->bookList = NULL;
    return node;
}

GenreNode* insertSubGenre(GenreNode* parent, const char* subGenreName) {
    if (!parent) return NULL;

    GenreNode* newNode = createGenreNode(subGenreName);
    newNode->pr = parent;

    if (!parent->fs) {
        parent->fs = newNode;
    } else {
        GenreNode* temp = parent->fs;
        while (temp->nb) temp = temp->nb;
        temp->nb = newNode;
    }
    return newNode;
}

void traverseGenreTree(GenreNode* root, int depth) {
    if (!root) return;

    for (int i = 0; i < depth; i++) printf("  ");
    printf("- %s\n", root->genreName);

    traverseGenreTree(root->fs, depth + 1);
    traverseGenreTree(root->nb, depth);
}

GenreNode* findGenre(GenreNode* root, const char* name) {
    if (!root) return NULL;
    if (strcmp(root->genreName, name) == 0) return root;

    GenreNode* found = findGenre(root->fs, name);
    if (found) return found;

    return findGenre(root->nb, name);
}

void deleteGenre(GenreNode* root, const char* targetName) {
    if (!root || !targetName) return;

    GenreNode* pr = root;
    GenreNode* prev = NULL;
    GenreNode* curr = root->fs;

    while (curr) {
        if (strcmp(curr->genreName, targetName) == 0) {
            if (prev) prev->nb = curr->nb;
            else pr->fs = curr->nb;

            free(curr);
            printf("Genre '%s' berhasil dihapus.\n", targetName);
            return;
        }
        prev = curr;
        curr = curr->nb;
    }

    GenreNode* child = root->fs;
    while (child) {
        deleteGenre(child, targetName);
        child = child->nb;
    }
}

GenreNode* loadGenreTreeFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("File genre tidak ditemukan.\n");
        return NULL;
    }

    GenreNode* root = createGenreNode("root");
    GenreNode* stack[100] = { NULL };
    stack[0] = root;

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        int level = 0;
        while (line[level] == '\t') level++;
        line[strcspn(line, "\n")] = 0;

        char* genreName = line + level;
        GenreNode* node = insertSubGenre(stack[level], genreName);
        stack[level + 1] = node;
    }

    fclose(file);
    return root;
}

void saveGenreTreeToFile(FILE* file, GenreNode* node, int depth) {
    if (!node) return;

    for (int i = 0; i < depth; i++) fprintf(file, "\t");
    fprintf(file, "%s\n", node->genreName);

    saveGenreTreeToFile(file, node->fs, depth + 1);
    saveGenreTreeToFile(file, node->nb, depth);
}

void saveGenreTree(GenreNode* root, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Gagal menyimpan genre ke file.\n");
        return;
    }
    saveGenreTreeToFile(file, root->fs, 0);
    fclose(file);
}