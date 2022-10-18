//
//  ProbabilityMatrixViewModel.swift
//  modelingLabwork3
//
//  Created by Andrej Hurynovič on 17.10.22.
//

import SwiftUI

class ProbabilityMatrixViewModel: ObservableObject {
    
    @Published var entities: Entities!
    @Published var initialState: Int = 0
    @Published var stableStateResults: [(Int, Double)] = []
    @Published var absorbingStateResults: [Double] = []
    @Published var selectedPreset: ProbabilitiesMatrixPresets = .stableState
    
    @Published var probabilitiesArray: [[String]] = ProbabilitiesMatrixPresets.stableState.probabilitiesArray
    
    @Published var stateNumbers: Int = ProbabilitiesMatrixPresets.stableState.stateNumbers
    var stateNumbersArray: [Int] {
        Array(0..<stateNumbers)
    }
    
    var columns: [GridItem] {
        var columns = [GridItem(.flexible(minimum: 25, maximum: 100))]
        columns.append(contentsOf: [GridItem](repeating: GridItem(), count: stateNumbers))
        return columns
    }
    
    func setPreset(selectedPreset: ProbabilitiesMatrixPresets) {
        withAnimation {
            updateProbabilitiesArray(stateNumbers: selectedPreset.stateNumbers)
            probabilitiesArray = selectedPreset.probabilitiesArray
            if initialState > stateNumbers - 2 {
                initialState -= 1
            }
        }
    }
    
    
    func updateProbabilitiesArray(stateNumbers: Int) {
        self.probabilitiesArray = [[String]] (repeating: [String] (repeating: "", count: stateNumbers), count: stateNumbers)
        self.stableStateResults = []
        self.absorbingStateResults = []
        self.stateNumbers = stateNumbers
    }
    
    //MARK: Stepper
    func stepperIncrement() {
        updateProbabilitiesArray(stateNumbers: stateNumbers + 1)
    }
    
    func stepperDecrement() {
        if stateNumbers > 2 {
            if initialState > stateNumbers - 2 {
                initialState -= 1
            }
            updateProbabilitiesArray(stateNumbers: stateNumbers - 1)
        }
    }
    
    //MARK: Button
    var disableCriteria: Bool {
        !(probabilitiesArray.allSatisfy { $0.allSatisfy { Double($0) != nil} })
    }
    
    func createEntities() {
        var entities: [Entity] = []
        
        for probabilities in probabilitiesArray {
            entities.append(Entity(transitionsProbabilities: probabilities.map( { Int(Double($0)! * 100) } )))
        }
        
        self.entities = Entities(entities: entities, initialState: initialState)
    }
    
    func calculateStableState() {
        createEntities()
    }
    
    func calculateAbsorbingStateSteps() {
        createEntities()
    }
    
}
