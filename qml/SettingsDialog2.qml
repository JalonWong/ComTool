import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.2
import QtQuick.Window 2.2

Dialog {
    id: settingsDialg
    title: qsTr("Settings")
//    flags: Qt.Dialog
    width: groupBox1.width
    height: groupBox1.height
//    maximumWidth: width
//    minimumWidth: width
//    maximumHeight: height
//    minimumHeight: height
        standardButtons: StandardButton.Apply
    GroupBox {
        id: groupBox1
        title: qsTr("Serial Port Settings")

        Column {
            Item {height: 10; width: parent.width}
            Grid {
                id: grid1
                columns: 2
                spacing: 5
                Label {
                    text: qsTr("Baud Rate:")
                }
                ComboBox {
                    model: [ "1200", "2400", "4800", "9600", "19200", "38400", "57600", "115200" ]
                }
                Label {
                    text: qsTr("Data bits:")
                }
                ComboBox {
                    model: [ "5", "6", "7", "8" ]
                }
                Label {
                    text: qsTr("Parity:")
                }
                ComboBox {
                    model: [ "None", "Even", "Odd", "Space", "Mark" ]
                }
                Label {
                    text: qsTr("Stop bits:")
                }
                ComboBox {
                    model: [ "1", "1.5", "2" ]
                }
                Label {
                    text: qsTr("Flow control:")
                }
                ComboBox {
                    model: [ "None", "RTS/CTS", "XON/XOFF" ]
                }
            }
        }
    }
}

