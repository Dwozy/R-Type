/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** main
*/

#include <iostream>
#include <cstdlib>
#include "SparseArray.hpp"
#include "Registry.hpp"

int main()
{
    // SparseArray<int> array;

    // const auto &at = array.insert_at(10, 5);
    // const auto &at = array[10];
    // std::cout << std::addressof(at) << std::endl;
    // std::cout << array.size() << std::endl;
    // for (std::size_t i = 0; i < array.size(); i++)
    // {
    //     if (array[i].has_value())
    //         std::cout << i << ". " << array[i].value() << std::endl;
    //     else
    //         std::cout << i << ". none" << std::endl;
    // }
    // std::cout << array.getIndex(at) << std::endl;



    Registry registry;
    Entity entity = registry.spawnEntity();
    Entity entity2 = registry.spawnEntity();
    Entity entity3 = registry.spawnEntity();
    Entity entity4 = registry.spawnEntity();
    Entity entity5 = registry.spawnEntity();

    registry.killEntity(entity3);
    entity3 = registry.spawnEntity();
    std::cout << "ENTITY3: " << entity3 << std::endl;
    std::cout << "ENTITY4: " << entity4 << std::endl;
    std::cout << "ENTITY5: " << entity5 << std::endl;
    auto &sa = registry.registerComponent<int>();
    // sa.insert_at(entity, 5);
    // sa.insert_at(10, 10);
    // registry.addComponent<int>(entity, 5);
    registry.removeComponent<int>(entity);
    registry.registerComponent<float>().insert_at(entity2, 2);
    auto &array = registry.getComponent<int>();
    // array.emplace_at(1, 2, 3, 4);
    registry.emplaceComponent<int>(entity3, entity2, entity4);
    // registry.addComponent<int>(entity5, 10);
    for (std::size_t i = 0; i < array.size(); i++)
    {
        if (array[i].has_value())
            std::cout << i << ". " << array[i].value() << std::endl;
        else
            std::cout << i << ". none" << std::endl;
    }
    return 0;
}
