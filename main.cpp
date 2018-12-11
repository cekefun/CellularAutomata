#include "cellular-automata/evolution/EvolutionFunctionRule.hpp"
#include "cellular-automata/evolution/EvolutionFunctionLife.hpp"
#include "cellular-automata/storage/ArrayMapper1D.hpp"
#include "cellular-automata/storage/ArrayMapper2D.hpp"
#include "cellular-automata/storage/FlexibleArrayImpl.hpp"
#include "cellular-automata/Simulator.hpp"

#include <iostream>

#include <unistd.h>

using namespace CellularAutomata;

void runSimulation1D(std::size_t elementSize, std::int64_t min, std::int64_t max, std::uint8_t rule) {
    ElementsDefinition elementsDefinition { { { ElementsDefinition::Type::BOOL, 0 } } };

    auto data = std::make_shared<ArrayMapper1D>(elementSize, min, max);
    auto mapper = std::make_shared<ElementMapper>(elementsDefinition);

    mapper->map<bool>((*data)(Index { (min + max) / 2 })) = true;

    Simulator sim(std::move(data),
                  std::move(mapper),
                  std::make_shared<EvolutionFunctionRule>(rule));

    for (unsigned int i = 0; i < 30; ++i) {
        sim.step();
    }

    sim.printResult();
}

void runSimulationBlinker() {
    ElementsDefinition elementsDefinition { { { ElementsDefinition::Type::BOOL, 0 } } };

    auto data = std::make_shared<ArrayMapper2D>(1, 0, 0, 5, 5);
    auto mapper = std::make_shared<ElementMapper>(elementsDefinition);

    mapper->map<bool>((*data)(Index { 2, 1 })) = true;
    mapper->map<bool>((*data)(Index { 2, 2 })) = true;
    mapper->map<bool>((*data)(Index { 2, 3 })) = true;

    Simulator sim(std::move(data),
                  std::move(mapper),
                  std::make_shared<EvolutionFunctionLife>(std::bitset<8> { 1 << 3 }, std::bitset<8> { 1 << 2 | 1 << 3 }));

    for (unsigned int i = 0; i < 8; ++i) {
        sim.step();
    }

    sim.printResult();
}

void test() {
    ArrayMapper1D data1(1, -5, 12);
    ArrayMapper1D data2(2, -5, 12);
    ArrayMapper1D data4(4, -5, 12);
    ArrayMapper1D data8(8, -5, 12);

    auto impl1 = reinterpret_cast<IFlexibleArrayImpl *>(data1._backend()._impl());
    auto impl2 = reinterpret_cast<IFlexibleArrayImpl *>(data2._backend()._impl());
    auto impl4 = reinterpret_cast<IFlexibleArrayImpl *>(data4._backend()._impl());
    auto impl8 = reinterpret_cast<IFlexibleArrayImpl *>(data8._backend()._impl());

    std::printf("Reported size:   %-4td                 %-4td                   %-4td                       %-4td\n",
                impl1->size(), impl2->size(), impl4->size(), impl8->size());
    std::printf("Divided by n:    %-4td                 %-4td                   %-4td                       %-4td\n",
                impl1->size() / 1, impl2->size() / 2, impl4->size() / 4, impl8->size() / 8);
    std::printf("Allocated bytes: %-4td                 %-4td                   %-4td                       %-4td\n",
                impl1->allocated_bytes(), impl2->allocated_bytes(), impl4->allocated_bytes(), impl8->allocated_bytes());
    std::printf("Divided by 16:   %-4td                 %-4td                   %-4td                       %-4td\n",
                impl1->allocated_bytes() / 16, impl2->allocated_bytes() / 16, impl4->allocated_bytes() / 16, impl8->allocated_bytes() / 16);
    std::printf("Unused bytes:    %-4td                 %-4td                   %-4td                       %-4td\n",
                impl1->allocated_bytes() - impl1->size(), impl2->allocated_bytes() - impl2->size(),
                impl4->allocated_bytes() - impl4->size(), impl8->allocated_bytes() - impl8->size());

    for (std::int64_t i = -16; i < 16; ++i) {
        if (i < -5) {
            std::printf("\033[90m");
        } else if (i < 12) {
            std::printf("\033[94m");
        } else {
            std::printf("\033[97m");
        }
        std::printf(" %3ld: %08jX = %02X        %08jX = %04X        %08jX = %08X        %08jX = %016lX\n", i,
                    reinterpret_cast<std::uint64_t>(data1(Index(i))), *(reinterpret_cast<std::uint8_t *>(data1(Index(i)))),
                    reinterpret_cast<std::uint64_t>(data2(Index(i))), *(reinterpret_cast<std::uint16_t *>(data2(Index(i)))),
                    reinterpret_cast<std::uint64_t>(data4(Index(i))), *(reinterpret_cast<std::uint32_t *>(data4(Index(i)))),
                    reinterpret_cast<std::uint64_t>(data8(Index(i))), *(reinterpret_cast<std::uint64_t *>(data8(Index(i))))
        );
        std::printf("\033[0m");
    }

    auto items1 = data1.indexes();

    for (const Index & item : items1) {
        std::printf("Index: %d(%ld, %ld, %ld)\n", static_cast<unsigned int>(item.dimensionality) + 1, item.x, item.y, item.z);
    }
}

int main() {
    long pageSize = sysconf(_SC_PAGESIZE);

    std::printf("sizeof(long long) = %td\n", sizeof(long long));
    std::printf("Page size: %ld\n", pageSize);

    runSimulation1D(1, -32, 32, 30);
    runSimulation1D(1, -32, 32, 126);
    runSimulation1D(1, -32, 32, 255);

    runSimulationBlinker();

    // test();

    return 0;
}
