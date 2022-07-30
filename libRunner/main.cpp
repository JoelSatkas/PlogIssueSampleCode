#include <cstdio>
#include <unordered_map>
#include <chrono>
#include <thread>
#include <memory>

#include "LibLoader.h"

int main()
{
    printf("hello from %s!\n", "libRunner");

    std::unordered_map<unsigned int, std::shared_ptr<CLibLoader>> m_LibID2LibMap;

    for (int index = 0; index < 30; index++)
    {
        printf("Creating lib loader %i!\n", index);

        std::shared_ptr<CLibLoader> pBriteDriverLoad = std::make_shared<CLibLoader>(index);
        pBriteDriverLoad->Load();
        pBriteDriverLoad->InitializeLib();

        m_LibID2LibMap[index] = pBriteDriverLoad;
    }

    printf("Finished creating all libs, will sleep for 5 seconds.\n");
    
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    return 0;
}