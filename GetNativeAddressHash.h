DWORD GetNativeAddressFromHash(DWORD dwNativeHash) {
    const DWORD dwModulator = *(DWORD*)0x831927A4;

    if (dwModulator == 0) {
        return 0;
    }

    const DWORD hashTableBase = *(DWORD*)0x831927A0;

    DWORD currentHash = dwNativeHash;
    int currentIndex = dwNativeHash % dwModulator;

    const int HASH_ENTRY_SIZE = 8;
    const int FUNCTION_ADDR_OFFSET = 4;

    while (true)
    {
        const DWORD* pHashEntry = (DWORD*)(hashTableBase + HASH_ENTRY_SIZE * currentIndex);
        const DWORD storedHash = *pHashEntry;

        if (storedHash == dwNativeHash) {
            return *(pHashEntry + 1);
        }

        if (storedHash <= 1) {
            return 0;
        }

        currentHash = (currentHash >> 1) + 1;
        currentIndex = (currentHash + currentIndex) % dwModulator;
    }
}
