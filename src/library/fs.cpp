// fs.cpp: File System

#include "sfs/fs.h"

#include <algorithm>
#include <vector>

#include <assert.h>
#include <stdio.h>
#include <string.h>

// Debug file system -----------------------------------------------------------

void FileSystem::debug(Disk *disk) {
    Block block;

    // Read Superblock
    disk->read(0, block.Data);

    printf("SuperBlock:\n");

    if (block.Super.MagicNumber == FileSystem::MAGIC_NUMBER) {
        printf("    magic number is valid\n");
    }
    else {
        printf("    magic number is not valid\n");
        return;
    }

    printf("    %u blocks\n"         , block.Super.Blocks);
    printf("    %u inode blocks\n"   , block.Super.InodeBlocks);
    printf("    %u inodes\n"         , block.Super.Inodes);

    // Read Inode blocks
    for (size_t i = 0; i < block.Super.InodeBlocks; i++) {
        Block InodeBlock;
        disk->read(i + 1, InodeBlock.Data);
        for (size_t j = 0; j < INODES_PER_BLOCK; j++) {
            if (InodeBlock.Inodes[j].Valid) {
                printf("Inode %zu:\n", i * FileSystem::INODES_PER_BLOCK + j);
                printf("    size: %u bytes\n", InodeBlock.Inodes[j].Size);

                std::vector<uint32_t> directBlocks;
                for (size_t k = 0; k < POINTERS_PER_INODE; k++) {
                    if (InodeBlock.Inodes[j].Direct[k] != 0) {
                        directBlocks.push_back(InodeBlock.Inodes[j].Direct[k]);
                    }
                }
                if (!directBlocks.empty()) {
                    printf("    direct blocks:");
                    for (uint32_t directBlock : directBlocks) {printf(" %u", directBlock);}
                    printf("\n");
                }
            }
        }
    }
}

// Format file system ----------------------------------------------------------

bool FileSystem::format(Disk *disk) {
    // Write superblock
    Block block;

    // Read Superblock
    disk->read(0, block.Data);

    block.Super.MagicNumber = 0xf0f03410;
    uint32_t NewInodesBlocks = block.Super.Blocks * 0.1;

    // Clear all otherp blocks
    return true;
}

// Mount file system -----------------------------------------------------------

bool FileSystem::mount(Disk *disk) {
    // Read superblock

    // Set device and mount

    // Copy metadata

    // Allocate free block bitmap

    return true;
}

// Create inode ----------------------------------------------------------------

ssize_t FileSystem::create() {
    // Locate free inode in inode table

    // Record inode if found
    return 0;
}

// Remove inode ----------------------------------------------------------------

bool FileSystem::remove(size_t inumber) {
    // Load inode information

    // Free direct blocks

    // Free indirect blocks

    // Clear inode in inode table
    return true;
}

// Inode stat ------------------------------------------------------------------

ssize_t FileSystem::stat(size_t inumber) {
    // Load inode information
    return 0;
}

// Read from inode -------------------------------------------------------------

ssize_t FileSystem::read(size_t inumber, char *data, size_t length, size_t offset) {
    // Load inode information

    // Adjust length

    // Read block and copy to data
    return 0;
}

// Write to inode --------------------------------------------------------------

ssize_t FileSystem::write(size_t inumber, char *data, size_t length, size_t offset) {
    // Load inode
    
    // Write block and copy to data
    return 0;
}
