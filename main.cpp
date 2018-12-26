#include "cellular-automata/evolution/EvolutionFunctionLangtonsAnt.hpp"
#include "cellular-automata/evolution/EvolutionFunctionRule.hpp"
#include "cellular-automata/evolution/EvolutionFunctionLife.hpp"
#include "cellular-automata/storage/ArrayMapper1D.hpp"
#include "cellular-automata/storage/ArrayMapper2D.hpp"
#include "cellular-automata/storage/FlexibleArrayImpl.hpp"
#include "cellular-automata/Simulator.hpp"

#include "cellular-automata/profiler.hpp"

#include <iostream>

#include <unistd.h>

using namespace CellularAutomata;

void runSimulation1D(std::size_t elementSize, std::int64_t min, std::int64_t max, std::uint8_t rule) {
    PROFILER_METHOD("main-test:1D");

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
    PROFILER_METHOD("main-test:blinker");

    ElementsDefinition elementsDefinition { { { ElementsDefinition::Type::BOOL, 0 } } };

    auto data = std::make_shared<ArrayMapper2D>(1, 0, 0, 5, 5);
    auto mapper = std::make_shared<ElementMapper>(elementsDefinition);

    mapper->map<bool>((*data)(Index { 2, 1 })) = true;
    mapper->map<bool>((*data)(Index { 2, 2 })) = true;
    mapper->map<bool>((*data)(Index { 2, 3 })) = true;

    Simulator sim(std::move(data),
                  std::move(mapper),
                  std::make_shared<EvolutionFunctionLife>(std::bitset<8> { 0b1000 }, std::bitset<8> { 0b1100 }));

    for (unsigned int i = 0; i < 8; ++i) {
        sim.step();
    }

    sim.printResult();
}

void runSimulationPulsar() {
    PROFILER_METHOD("main-test:pulsar");

    ElementsDefinition elementsDefinition { { { ElementsDefinition::Type::BOOL, 0 } } };

    auto data = std::make_shared<ArrayMapper2D>(1, 0, 0, 17, 17);
    auto mapper = std::make_shared<ElementMapper>(elementsDefinition);

    // Top left quadrant
    mapper->map<bool>((*data)(Index { 2, 4 })) = true;
    mapper->map<bool>((*data)(Index { 2, 5 })) = true;
    mapper->map<bool>((*data)(Index { 2, 6 })) = true;
    mapper->map<bool>((*data)(Index { 4, 2 })) = true;
    mapper->map<bool>((*data)(Index { 5, 2 })) = true;
    mapper->map<bool>((*data)(Index { 6, 2 })) = true;
    mapper->map<bool>((*data)(Index { 7, 4 })) = true;
    mapper->map<bool>((*data)(Index { 7, 5 })) = true;
    mapper->map<bool>((*data)(Index { 7, 6 })) = true;
    mapper->map<bool>((*data)(Index { 4, 7 })) = true;
    mapper->map<bool>((*data)(Index { 5, 7 })) = true;
    mapper->map<bool>((*data)(Index { 6, 7 })) = true;
    // Top right quadrant
    mapper->map<bool>((*data)(Index { 2, 10 })) = true;
    mapper->map<bool>((*data)(Index { 2, 11 })) = true;
    mapper->map<bool>((*data)(Index { 2, 12 })) = true;
    mapper->map<bool>((*data)(Index { 4, 14 })) = true;
    mapper->map<bool>((*data)(Index { 5, 14 })) = true;
    mapper->map<bool>((*data)(Index { 6, 14 })) = true;
    mapper->map<bool>((*data)(Index { 7, 10 })) = true;
    mapper->map<bool>((*data)(Index { 7, 11 })) = true;
    mapper->map<bool>((*data)(Index { 7, 12 })) = true;
    mapper->map<bool>((*data)(Index { 4, 9 })) = true;
    mapper->map<bool>((*data)(Index { 5, 9 })) = true;
    mapper->map<bool>((*data)(Index { 6, 9 })) = true;
    // Bottom left quadrant
    mapper->map<bool>((*data)(Index { 14, 4 })) = true;
    mapper->map<bool>((*data)(Index { 14, 5 })) = true;
    mapper->map<bool>((*data)(Index { 14, 6 })) = true;
    mapper->map<bool>((*data)(Index { 10, 2 })) = true;
    mapper->map<bool>((*data)(Index { 11, 2 })) = true;
    mapper->map<bool>((*data)(Index { 12, 2 })) = true;
    mapper->map<bool>((*data)(Index { 9, 4 })) = true;
    mapper->map<bool>((*data)(Index { 9, 5 })) = true;
    mapper->map<bool>((*data)(Index { 9, 6 })) = true;
    mapper->map<bool>((*data)(Index { 10, 7 })) = true;
    mapper->map<bool>((*data)(Index { 11, 7 })) = true;
    mapper->map<bool>((*data)(Index { 12, 7 })) = true;
    // Bottom right quadrant
    mapper->map<bool>((*data)(Index { 14, 10 })) = true;
    mapper->map<bool>((*data)(Index { 14, 11 })) = true;
    mapper->map<bool>((*data)(Index { 14, 12 })) = true;
    mapper->map<bool>((*data)(Index { 10, 14 })) = true;
    mapper->map<bool>((*data)(Index { 11, 14 })) = true;
    mapper->map<bool>((*data)(Index { 12, 14 })) = true;
    mapper->map<bool>((*data)(Index { 9, 10 })) = true;
    mapper->map<bool>((*data)(Index { 9, 11 })) = true;
    mapper->map<bool>((*data)(Index { 9, 12 })) = true;
    mapper->map<bool>((*data)(Index { 10, 9 })) = true;
    mapper->map<bool>((*data)(Index { 11, 9 })) = true;
    mapper->map<bool>((*data)(Index { 12, 9 })) = true;

    Simulator sim(std::move(data),
                  std::move(mapper),
                  std::make_shared<EvolutionFunctionLife>(std::bitset<8> { 0b1000 }, std::bitset<8> { 0b1100 }));

    for (unsigned int i = 0; i < 16; ++i) {
        sim.step();
    }

    sim.printResult();
}

void runSimulationLangtonsAnt() {
    PROFILER_METHOD("main-test:ant");

    constexpr std::uint8_t size_bool = ElementsDefinition::type_size<ElementsDefinition::Type::BOOL>();
    constexpr std::uint8_t size_int8 = ElementsDefinition::type_size<ElementsDefinition::Type::INT8>();


    ElementsDefinition def { {
                                 { ElementsDefinition::Type::BOOL, 0 }, // Color
                                 { ElementsDefinition::Type::INT8, size_bool } // Ant
                             } };

    auto data = std::make_shared<ArrayMapper2D>(size_bool + size_int8, 0, 0, 37, 33);
    auto mapper = std::make_shared<ElementMapper>(def);

    mapper->map<std::int8_t>((*data)(Index { 11, 11 }), 1) = 1; // Place the ant

    Simulator sim(std::move(data),
                  std::move(mapper),
                  std::make_shared<EvolutionFunctionLangtonsAnt>());

    for (unsigned int i = 0; i < 4000; ++i) {
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

    auto sectionVisitor = [](const profiler::Section & section) {
        std::printf("%s: %.6f seconds\n", section.path().c_str(), static_cast<double>(section.time().count()) / 1000000000.0);
    };

    /*
    {
        PROFILER_RESET;
        runSimulation1D(1, -32, 32, 30);
        PROFILER_COLLECT(sectionVisitor);
    }
    std::printf("\n\n");
    {
        PROFILER_RESET;
        runSimulation1D(1, -32, 32, 126);
        PROFILER_COLLECT(sectionVisitor);
    }
    std::printf("\n\n");
    {
        PROFILER_RESET;
        runSimulation1D(1, -32, 32, 255);
        PROFILER_COLLECT(sectionVisitor);
    }
    std::printf("\n\n");
    {
        PROFILER_RESET;
        runSimulationBlinker();
        PROFILER_COLLECT(sectionVisitor);
    }
    std::printf("\n\n");
    {
        PROFILER_RESET;
        runSimulationPulsar();
        PROFILER_COLLECT(sectionVisitor);
    }
    std::printf("\n\n");
    {
        PROFILER_RESET;
        runSimulationLangtonsAnt();
        PROFILER_COLLECT(sectionVisitor);
    }
    //*/

    //*
    PROFILER_RESET;
    runSimulation1D(1, -32, 32, 30);
    runSimulation1D(1, -32, 32, 126);
    runSimulation1D(1, -32, 32, 255);
    runSimulationBlinker();
    runSimulationPulsar();
    runSimulationLangtonsAnt();
    PROFILER_COLLECT(sectionVisitor);
    //*/

    // test();

    return 0;
}
