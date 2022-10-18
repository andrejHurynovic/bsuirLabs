//
//  RandomNumbersViewModel.swift
//  modelingLabwork3
//
//  Created by Andrej Hurynovič on 17.10.22.
//

import Foundation

class RandomNumbersViewModel: ObservableObject {
    @Published var initial = "32"
    @Published var a = "911"
    @Published var c = "733"
    @Published var m = "101"
    @Published var iterations = "100"
    
    @Published var useSwiftMathRandomGenerator = true
    
    var buttonDisableCriteria: Bool {
        if useSwiftMathRandomGenerator {
            return Int(iterations) == nil
        } else {
            return ![initial, a, c, m, iterations].allSatisfy { Int($0) != nil }
        }
    }

    func restoreToDefaults() {
        initial = "37"
        a = "131"
        c = "1021"
        m = "101"
        iterations = "100"
        useSwiftMathRandomGenerator = true
    }
    
    func calculateRandomNumbersArray() -> [Int] {
        if useSwiftMathRandomGenerator {
            return (0...100).randomElements(Int(iterations)!)
        } else {
            var array: [Int] = []
            
            var initial = Int(initial)!
            for _ in 1...Int(iterations)! {
                initial = Int(Int(a)! * initial + Int(c)!) % Int(m)!
                array.append(initial)
            }
            return array
        }
    }
    
}
