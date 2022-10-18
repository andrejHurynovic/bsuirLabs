//
//  ProbabilityMatrixView.swift
//  modelingLabwork3
//
//  Created by Andrej Hurynovič on 15.10.22.
//

import SwiftUI

struct ProbabilityMatrixView:  View {
    
    @Binding var randomNumbersArray: [Int]
    @ObservedObject var viewModel = ProbabilityMatrixViewModel()
    
    var body: some View {
        List {
            header
            Divider()
            grid
            Spacer()
            buttons
        }
    }
    
    
    
    //MARK: Header
    var header: some View {
        HStack {
            Text("Probability matrix")
                .font(.title)
                .fontWeight(.bold)
            Spacer()
            presetsPicker
            Divider()
            statesNumberPicker
        }
    }
    
    var presetsPicker: some View {
        Picker("Presets", selection: $viewModel.selectedPreset) {
            ForEach(ProbabilitiesMatrixPresets.allCases, id: \.self) { theCase in
                Text(String(theCase.description))
                    .tag(theCase)
            }
        }
        .onChange(of: viewModel.selectedPreset) { newValue in
                viewModel.setPreset(selectedPreset: newValue)
        }
    }
    
    var statesNumberPicker: some View {
        Stepper {
            Text("Number of states \(viewModel.stateNumbers)")
        } onIncrement: {
            viewModel.stepperIncrement()
        } onDecrement: {
            viewModel.stepperDecrement()
        }
    }
    
    
    
    //MARK: Grid
    var grid: some View {
        LazyVGrid(columns: viewModel.columns, content: {
            gridHeader
            probabilitiesGrid
            stableStateProbabilities
            absorbingStateSteps
        })
        .multilineTextAlignment(.center)
        .textFieldStyle(RoundedBorderTextFieldStyle())
    }
    
    var gridHeader: some View {
        Group {
            Text("")
            ForEach(viewModel.stateNumbersArray, id: \.self) { stateNumber in
                Text("S\(stateNumber)")
            }
        }
    }
    
    var probabilitiesGrid: some View {
        ForEach(viewModel.stateNumbersArray, id: \.self) { groupStateNumber in
            Group {
                Text("S\(groupStateNumber)")
                ForEach(viewModel.stateNumbersArray, id: \.self) { columnStateNumber in
                    TextField("", text: $viewModel.probabilitiesArray[groupStateNumber][columnStateNumber]).id("\(columnStateNumber) - \(groupStateNumber)")
                }
            }
        }
    }
    
    @ViewBuilder var stableStateProbabilities: some View {
        if !viewModel.stableStateResults.isEmpty {
            let results = viewModel.stableStateResults
            Group {
                Text("Iterations")
                ForEach(results.indices, id: \.self) { resultIndex in
                    let (iterations, _) = results[resultIndex]
                    Text(String(iterations))
                        .id("\(resultIndex) - iterations")
                }
                
            }
            Group {
                Text("Probability")
                ForEach(results.indices, id: \.self) { resultIndex in
                    let (_, probability) = results[resultIndex]
                    Text(String(probability))
                        .id("\(resultIndex) - probability")
                }
                
            }
        }
    }
    
    @ViewBuilder var absorbingStateSteps: some View {
        if !viewModel.absorbingStateResults.isEmpty {
            let results = viewModel.absorbingStateResults
            Group {
                Text("Steps")
                ForEach(results.indices, id: \.self) { resultIndex in
                    let steps = results[resultIndex]
                    Text(String(round(steps * 100) / 100.0))
                        .id("\(resultIndex) - absorbing")
                }
                
            }
        }
    }
    
    
    
        //MARK: Buttons
    var buttons: some View {
        HStack {
            calculateStableStateButton
            calculateAbsorbingStateSteps
            Spacer()
            Divider()
            initialStateStepper
        }
    }
    
    var calculateStableStateButton : some View {
            Button {
                viewModel.calculateStableState()
                withAnimation {
                    viewModel.stableStateResults = viewModel.entities.calculateStableState(from: randomNumbersArray)
                }
            } label: {
                Text("Calculate stable state 😀🤓😎")
            }
            .keyboardShortcut(.defaultAction)
            .disabled(viewModel.disableCriteria)
    }
    
    var calculateAbsorbingStateSteps : some View {
            Button {
                viewModel.calculateAbsorbingStateSteps()
                withAnimation {
                    viewModel.absorbingStateResults = viewModel.entities.calculateAbsorbingStateSteps(from: randomNumbersArray)
                }
            } label: {
                Text("Calculate absorbing state steps")
            }
            .keyboardShortcut(.defaultAction)
            .disabled(viewModel.disableCriteria)
    }
    
    var initialStateStepper: some View {
        Stepper(value: $viewModel.initialState, in: 0...(viewModel.stateNumbers - 1)) {
            Text("Initial state \(viewModel.initialState)")
        }
    }
    
    
}

struct ProbabilityMatrixView_Preview: PreviewProvider {
    static var previews: some View {
        ProbabilityMatrixView(randomNumbersArray: .constant([10, 8, 49, 67, 1, 41, 29, 73, 80, 88, 25, 54, 15, 57, 4, 30, 2, 71, 20, 5, 60, 94, 3, 0, 11, 38, 40, 100, 82, 47, 7, 19, 76, 69, 61, 23, 95, 33, 92, 44, 18, 46, 78, 28, 43, 89, 55, 45, 48, 37, 10, 8, 49, 67, 1, 41, 29, 73, 80, 88, 25, 54, 15, 57, 4, 30, 2, 71, 20, 5, 60, 94, 3, 0, 11, 38, 40, 100, 82, 47, 7, 19, 76, 69, 61, 23, 95, 33, 92, 44, 18, 46, 78, 28, 43, 89, 55, 45, 48, 37]))
    }
}
