//
//  Entity.swift
//  Мод, ЛР № 3
//
//  Created by Andrej Hurynovič on 15.10.22.
//

import Foundation

class Entity {
    var transitionsProbabilities: [Double]
    var probabilitiesRanges: [Range<Double>] = []
    var hitsCounter: Int = 0
    
    init(transitionsProbabilities: [Double]) {
        self.transitionsProbabilities = transitionsProbabilities
        
        var currentProbability = 0.0
        for probability in transitionsProbabilities {
            probabilitiesRanges.append(currentProbability..<(probability + currentProbability))
            currentProbability += probability
        }
    }
    
    func next(probability: Double) -> Int {
        for index in probabilitiesRanges.indices {
            if probabilitiesRanges[index].contains(probability) {
                return index
            }
        }
        return probabilitiesRanges.count - 1
    }
    
    func hit() {
        hitsCounter += 1
    }
    
    func isAbsorbing(stateNumber: Int) -> Bool {
        return transitionsProbabilities[stateNumber] == 1.0
    }
    
    func cleanHitsCounter() {
        self.hitsCounter = 0
    }
    
}
