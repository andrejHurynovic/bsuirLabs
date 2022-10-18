//
//  ContentView.swift
//  ModelingLabwork3
//
//  Created by Andrej Hurynovič on 4.10.22.
//

import SwiftUI

struct ContentView: View {
    @State var randomNumbersArray: [Int] =  (0...100).randomElements(1000)
    
    var body: some View {
        NavigationView {
            List() {
                NavigationLink {
                    RandomNumbersView(randomNumbersArray: $randomNumbersArray)
                } label: {
                    Label("Random", systemImage: "number")
                }
                NavigationLink {
                    ProbabilityMatrixView(randomNumbersArray: $randomNumbersArray)
                } label: {
                    Label("Matrix", systemImage: "lanyardcard")
                }
            }
            .listStyle(SidebarListStyle())
        }
    }    
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
