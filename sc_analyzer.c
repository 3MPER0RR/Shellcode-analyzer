#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <capstone/capstone.h>


#define MAX_SHELLCODE 8192

void analyze_instruction(cs_insn *ins) {
    // Syscall detection
    if (strcmp(ins->mnemonic, "syscall") == 0 ||
        strcmp(ins->mnemonic, "int") == 0) {
        printf("  [!] SYSCALL INTERRUPT\n");
    }

    // Stack pivot / shellcode classic
    if (strstr(ins->mnemonic, "push") ||
        strstr(ins->mnemonic, "pop")) {
        printf("  [*] Stack operation\n");
    }

    // Execve pattern (very naive, phase 1)
    if (strcmp(ins->mnemonic, "mov") == 0 &&
        strstr(ins->op_str, "0x3b")) {
        printf("  [!] Possible execve syscall setup\n");
    }
}

int main(int argc, char **argv) {
    FILE *fp;
    uint8_t *code;
    size_t size;
    csh handle;
    cs_insn *insn;
    size_t count;
    uint64_t address = 0x0;

    if (argc != 2) {
        printf("Usage: %s shellcode.bin\n", argv[0]);
        return 1;
    }

    fp = fopen(argv[1], "rb");
    if (!fp) {
        perror("fopen");
        return 1;
    }

    code = malloc(MAX_SHELLCODE);
    if (!code) {
        perror("malloc");
        fclose(fp);
        return 1;
    }

    size = fread(code, 1, MAX_SHELLCODE, fp);
    fclose(fp);

    if (cs_open(CS_ARCH_X86, CS_MODE_64, &handle) != CS_ERR_OK) {
        printf("Failed to initialize Capstone\n");
        free(code);
        return 1;
    }

    cs_option(handle, CS_OPT_DETAIL, CS_OPT_ON);

    count = cs_disasm(handle, code, size, address, 0, &insn);

    if (count > 0) {
        for (size_t i = 0; i < count; i++) {
            printf("0x%04llx:\t%-8s %s\n",
                   insn[i].address,
                   insn[i].mnemonic,
                   insn[i].op_str);

            analyze_instruction(&insn[i]);
        }
        cs_free(insn, count);
    } else {
        printf("ERROR: Disassembly failed\n");
    }

    cs_close(&handle);
    free(code);
    return 0;
}
