//
//  MegaTextField.swift
//  Мод, ЛР № 3
//
//  Created by Andrej Hurynovič on 15.10.22.
//

import SwiftUI

struct MegaTextField: View {
    
    @State var description: String
    @Binding var string: String
    
    var body: some View {
        VStack(alignment: .leading, spacing: 4) {
            Text(description)
                .font(.caption)
                .foregroundColor(Color.gray)
            TextField(description, text: $string)
        }
    }
}
