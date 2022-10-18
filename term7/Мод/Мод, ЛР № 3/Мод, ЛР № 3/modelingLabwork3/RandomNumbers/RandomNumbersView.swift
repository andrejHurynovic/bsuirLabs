//
//  RandomNumbersView.swift
//  Мод, ЛР № 3
//
//  Created by Andrej Hurynovič on 15.10.22.
//

import SwiftUI

struct RandomNumbersView: View {
    
    @Binding var randomNumbersArray: [Int]
    @ObservedObject var viewModel = RandomNumbersViewModel()
    
    var body: some View {
        List {
            header
            Divider()
            textFields
            randomArray
            Spacer()
            calculateRandomNumbersButton
        }
    }
    
    var header: some View {
        HStack {
            Text("Random numbers")
                .font(.title)
                .fontWeight(.bold)
            Spacer()
            Toggle("Use Swift.Math random generator", isOn: $viewModel.useSwiftMathRandomGenerator.animation())
            Divider()
            Button {
                viewModel.restoreToDefaults()
            } label: {
                Text("Restore to defaults")
            }
        }

    }
    
    var textFields: some View {
        VStack {
            if !viewModel.useSwiftMathRandomGenerator {
                MegaTextField(description: "Initial value", string: $viewModel.initial)
                MegaTextField(description: "A", string: $viewModel.a)
                MegaTextField(description: "C", string: $viewModel.c)
                MegaTextField(description: "M", string: $viewModel.m)
            }
            MegaTextField(description: "Iterations", string: $viewModel.iterations)
        }
        .textFieldStyle(RoundedBorderTextFieldStyle())
    }
    
    @ViewBuilder var randomArray: some View {
        if randomNumbersArray.isEmpty == false {
            Divider()
            VStack(alignment: .leading, spacing: 4) {
                Text("Array of random numbers")
                    .font(.caption)
                    .foregroundColor(Color.gray)
                Text(randomNumbersArray.description)
            }
        }
    }
    
    var calculateRandomNumbersButton: some View {
        Button {
            withAnimation {
                randomNumbersArray =  viewModel.calculateRandomNumbersArray()
            }
        } label: {
            Text("Do math 🥲😤")
        }
        .keyboardShortcut(.defaultAction)
        .disabled(viewModel.buttonDisableCriteria)
    }
    
}

struct RandomNumbersView_Preview: PreviewProvider {
    static var previews: some View {
        RandomNumbersView(randomNumbersArray: .constant([]))
    }
}
