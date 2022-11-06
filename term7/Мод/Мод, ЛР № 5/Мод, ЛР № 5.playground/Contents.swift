
import Foundation

extension Double {
    var string: String {
        String((self * 100).rounded()/100)
    }
}

extension Array<Double> {
    func average() -> Double {
        return self.reduce(0, +) / Double(self.count)
    }
}




func calculateIncomeTime(_ seed: Double) -> Double {
    if Bool.random() {
        return log(2 * seed) + 2
    } else {
        return -log(-2 * seed + 2) + 2
    }
}

func calculateProcessingTime(_ seed: Double) -> Double {
    return -0.5 * log(1 - seed)
}



class Entity {
    var incomeTime: Double
    var processingTime: Double
    
    var processingRange: ClosedRange<Double>
    var waiting: Double
    
    var inactivity: Double
    
    init(seed: Double, previousIncomeTime: Double, previousProcessingEndTime: Double) {
        self.incomeTime = previousIncomeTime + calculateIncomeTime(seed)
        self.processingTime = calculateProcessingTime(seed)
        
        //processingRange
        if incomeTime >= previousProcessingEndTime {
            processingRange = incomeTime...(incomeTime + processingTime)
        } else {
            processingRange = previousProcessingEndTime...(previousProcessingEndTime + processingTime)
        }
        
        //waiting
        if processingRange.lowerBound == incomeTime {
            self.waiting = 0
        } else {
            self.waiting = processingRange.lowerBound - incomeTime
        }
        
        //inactivity
        if previousProcessingEndTime == incomeTime, self.waiting == 0 {
            self.inactivity = 0
        } else {
            self.inactivity = processingRange.lowerBound - previousProcessingEndTime
        }
    }
    
    func print() {
        Swift.print("Entity description:")
        Swift.print("incomeTime: \(self.incomeTime)")
        Swift.print("processingTime: \(self.processingTime)")
        Swift.print("processingRange: \(self.processingRange)")
        Swift.print("inactivity: \(self.inactivity)")
        Swift.print("waiting: \(self.waiting)")
        Swift.print("")
    }
    
}

var randomValues = [16, 26, 98, 97, 25, 97, 14, 71, 93, 11, 88, 21, 84, 13, 81, 82, 10, 41, 69, 96, 84, 20, 30, 59, 31, 88, 17, 81, 24, 42, 67, 41, 68, 61, 40, 40, 36, 95, 53, 51, 77, 19, 19, 30, 97, 23, 52, 81, 47, 95, 86, 36, 14, 95, 73, 10, 97, 27, 79, 82, 75, 95, 39, 80, 67, 90, 43, 39, 80, 58, 85, 35, 17, 84, 75, 86, 11, 24, 59, 26, 18, 96, 70, 20, 44, 47, 70, 66, 82, 92, 74, 21, 37, 85, 94, 13, 85, 13, 65, 58, 48, 70, 92, 68, 25, 67, 86, 79, 97, 17, 54, 29, 88, 93, 91, 86, 73, 98, 51, 77, 16, 75, 80, 35, 25, 39, 67, 30, 70, 87, 20, 91, 16, 98, 46, 17, 82, 70, 83, 55, 58, 76, 35, 96, 74, 29, 55, 21].map { Double($0) / 100 }

var entities: [Entity] = [Entity(seed: 0.45, previousIncomeTime: 0.0, previousProcessingEndTime: 0.0)]

for index in randomValues.indices {
    let entity = entities[index]
    entities.append(Entity(seed: randomValues[index], previousIncomeTime: entity.incomeTime, previousProcessingEndTime: entity.processingRange.upperBound))
}

func calculateAverageProcessing() {
    print("Average processing time: \(entities.map { $0.processingTime }.average().string)")
    print("")
}
func calculateAverageTimeInSystem() {
    print("Average time in system: \(entities.map { $0.processingRange.upperBound - $0.incomeTime }.average().string)")
    print("")
}

func averageEntitiesInSystem() {
    let allTime = entities.last!.processingRange.upperBound
    let allProcessingTime = entities.map { $0.processingRange.upperBound - $0.processingRange.lowerBound }.reduce(0, +)
    let allInactivity = entities.map { $0.inactivity }.reduce(0, +)
    let allWaiting = entities.map { $0.waiting }.reduce(0, +)
    
    let noEntities = allInactivity
    let oneEntity = allProcessingTime - allWaiting
    let twoEntities = allWaiting
    
    let noEntitiesPercentage = noEntities / allTime
    let oneEntityPercentage = oneEntity / allTime
    let twoEntitiesPercentage = twoEntities / allTime
    
    print("No entities: \((noEntitiesPercentage * 100).string)%")
    print("One entity: \((oneEntityPercentage * 100).string)%")
    print("Two entities: \((twoEntitiesPercentage * 100).string)%")
    
    let averageEntitiesInSystem = 0 * noEntitiesPercentage + 1 * oneEntityPercentage + 2 * twoEntitiesPercentage
    print("Average entities in system: \((averageEntitiesInSystem * 100).string)%")
    
    var average = [0.0]
    
    stride(from: 0.0, to: allTime, by: 0.1).forEach({ number in
        average.append(Double(entities.filter({ entity in
            (entity.incomeTime...entity.processingRange.upperBound).contains(number)
        }).count))
    })
    
    print("Average entities in system (alternative): \((average.average() * 100).string)%")
    print("")
    
    
}

func calculateActivityPercentage() {
    let allTime = entities.last!.processingRange.upperBound
    let allProcessingTime = entities.map { $0.processingRange.upperBound - $0.processingRange.lowerBound }.reduce(0, +)
    let allInactivity = entities.map { $0.inactivity }.reduce(0, +)
    
    print("Activity percentage: \(((allProcessingTime * 100) / allTime).string)%")
    print("Inactivity percentage: \(((allInactivity * 100) / allTime).string)%")
    print("Whole time: \(allTime.string)")
    print("Whole activity: \(allProcessingTime.string)")
    print("Whole inactivity: \(allInactivity.string)")
    print("")
}


calculateAverageProcessing()
calculateAverageTimeInSystem()
averageEntitiesInSystem()
calculateActivityPercentage()

