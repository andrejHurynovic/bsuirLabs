//
//  Entity.swift
//  Мод, ЛР № 3
//
//  Created by Andrej Hurynovič on 15.10.22.
//

import Foundation

class Entity {
    var transitionsProbabilities: [Int]
    var probabilitiesRanges: [ClosedRange<Int>] = []
    var hitsCounter: Int = 0
    
    init(transitionsProbabilities: [Int]) {
        self.transitionsProbabilities = transitionsProbabilities
        
        var currentProbability = 0
        for probability in transitionsProbabilities {
            //Ranges in form []
            probabilitiesRanges.append(currentProbability...(probability + currentProbability))
            currentProbability += probability
        }
    }
    
    ///Finds next state from probability
    func next(probability: Int) -> Int {
        for index in probabilitiesRanges.indices {
            if probabilitiesRanges[index].contains(probability) {
                return index
            }
        }
        return probabilitiesRanges.count - 1
    }
    
    func isAbsorbing(stateNumber: Int) -> Bool {
        return transitionsProbabilities[stateNumber] == 100
    }
    
    //MARK: Hits
    func hit() {
        hitsCounter += 1
    }
    func cleanHitsCounter() {
        self.hitsCounter = 0
    }
    
}
