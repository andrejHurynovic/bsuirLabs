//
//  Entities.swift
//  Мод, ЛР № 3
//
//  Created by Andrej Hurynovič on 15.10.22.
//

import Foundation

class Entities {
    var currentState: Int
    var currentEntity: Entity {
        entities[currentState]
    }
    var entities: [Entity]
    
    init(entities: [Entity], initialState: Int) {
        self.entities = entities
        self.currentState = initialState
    }
    
    func calculateStableState(from intArray: [Int]) -> [(Int, Double)] {
        let randomDoubles = intArray
        
        for probability in randomDoubles {
            currentState = currentEntity.next(probability: probability)
            entities[currentState].hit()
        }
        
        return entities.map {($0.hitsCounter, (Double($0.hitsCounter) / Double(randomDoubles.count)))}
    }
    
    func notAbsorbingAndAbsorbingIndexes() -> (notAbsorbingEntitiesIndexes: [Int], absorbingEntitiesIndexes: [Int]) {
        var notAbsorbingEntitiesIndexes: [Int] = []
        var absorbingEntitiesIndexes: [Int] = []
        for index in entities.indices {
            if !entities[index].isAbsorbing(stateNumber: index) {
                notAbsorbingEntitiesIndexes.append(index)
            } else {
                absorbingEntitiesIndexes.append(index)
            }
        }
        return (notAbsorbingEntitiesIndexes, absorbingEntitiesIndexes)
    }
    
    func calculateAbsorbingStateSteps(from intArray: [Int]) -> [Double] {
        let randomDoubles = intArray
        
        var hitsBeforeAbsorbingState: [Int: [Int]] = [:]
        
        let (notAbsorbingEntitiesIndexes, absorbingEntitiesIndexes) = notAbsorbingAndAbsorbingIndexes()
        
        for index in notAbsorbingEntitiesIndexes {
            hitsBeforeAbsorbingState[index] = []
            var localRandomDoubles = randomDoubles
            repeat {
                currentState = index
                repeat {
                    let nextEntityIndex = currentEntity.next(probability: localRandomDoubles.removeFirst())
                    currentEntity.hit()
                    if absorbingEntitiesIndexes.contains(nextEntityIndex) {
                        let hits = entities.map { $0.hitsCounter }.reduce(0, +)
                        hitsBeforeAbsorbingState[index]?.append(hits)
                        for entity in entities {
                            entity.cleanHitsCounter()
                        }
                        break
                    } else {
                        currentState = nextEntityIndex
                    }
                } while (!localRandomDoubles.isEmpty)
                
            } while (!localRandomDoubles.isEmpty)
            
        }
        
        var resultArray: [Double] = []
        
        for index in entities.indices {
            if notAbsorbingEntitiesIndexes.contains(index) {
                let steps = hitsBeforeAbsorbingState[index]!.reduce(0, +)
                let averageSteps = Double(steps) / Double(hitsBeforeAbsorbingState[index]!.count)
                resultArray.append(averageSteps)
            } else {
                resultArray.append(0)
            }
        }
        
        return resultArray
    }
    
}
