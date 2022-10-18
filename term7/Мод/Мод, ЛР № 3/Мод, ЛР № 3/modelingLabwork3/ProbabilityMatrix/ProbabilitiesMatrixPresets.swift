//
//  ProbabilitiesMatrixPresets.swift
//  modelingLabwork3
//
//  Created by Andrej Hurynovič on 17.10.22.
//

import Foundation

enum ProbabilitiesMatrixPresets: CaseIterable {
    case labWorkTwoStableState
    case labWorkTwoAbsorbingState
    case stableState
    case absorbingState
    case case0dot25
    
    var description: String {
        switch self {
        case .labWorkTwoStableState:
            return "Stable state (second labWork)"
        case .labWorkTwoAbsorbingState:
            return "Absorbing state (second labWork)"
        case .stableState:
            return "Stable state"
        case .absorbingState:
            return "Absorbing state"
        case .case0dot25:
            return "0.25"
        }
    }
    
    var stateNumbers: Int {
        switch self {
        case .stableState, .absorbingState:
            return 3
        case .case0dot25, .labWorkTwoStableState, .labWorkTwoAbsorbingState:
            return 4
        }
        
    }
    
    var probabilitiesArray: [[String]] {
        switch self {
        case .labWorkTwoStableState:
            return [["0.6","0.2","0.1", "0.1"],
                    ["0.3","0.4","0.1", "0.2"],
                    ["0.2","0.2","0.2", "0.4"],
                    ["0.3","0.3","0.3", "0.1"]]
        case .labWorkTwoAbsorbingState:
            return [["1","0","0", "0"],
                    ["0.3","0.4","0.1", "0.2"],
                    ["0","0","1", "0"],
                    ["0.3","0.3","0.3", "0.1"]]
        case .absorbingState:
            return [["1.0","0","0"],
                    ["0.3","0.4","0.3"],
                    ["0.2","0.4","0.4"]]
        case .stableState:
            return [["0.6","0.3","0.1"],
                    ["0.3","0.4","0.3"],
                    ["0.2","0.2","0.6"]]
        case .case0dot25:
            return [["0.25","0.25","0.25", "0.25"],
                    ["0.25","0.25","0.25", "0.25"],
                    ["0.25","0.25","0.25", "0.25"],
                    ["0.25","0.25","0.25", "0.25"]]
        }
        
    }
}
