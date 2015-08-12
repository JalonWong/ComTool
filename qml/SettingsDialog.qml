import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.2
import QtQuick.Window 2.2
import io.jalon.SerialPort 1.0
import io.jalon 1.0

Window {
    id: root
    title: qsTr("Settings")
    flags: Qt.Dialog
    modality: Qt.WindowModal
    width: 300
    height: 300
    maximumWidth: width
    minimumWidth: width
    maximumHeight: height
    minimumHeight: height

    property alias settingsMap: settingsMap

    onVisibleChanged: {
        if(visible){
            serialPort.getPortsInfo()
//            console.log("count", serialPort.portsMap.count())
//            console.log("[]", serialPort.portsMap["text"]);
//            portCombo.model = serialPort.portsMap.keys();
//            var tmp = SerialPort.Baud1200
//            console.log("enum", tmp)
//            serialPort.map.insert("data", "dd1")
//            console.log("map", serialPort.map2.value("data"))
        }
    }

    signal apply()

    EMap {
        id: settingsMap
        Component.onCompleted: {
            console.debug("Settings map completed")
            serialPort.loadSettings(settingsMap)
            settingsToValues()
        }

        function valuesToSettings() {
            insert("COM", portCombo.currentText)
            insert("BaudRate", getValue(baudRateCombo))
            insert("DataBits", getValue(dataCombo))
            insert("Parity", getValue(parityCombo))
            insert("StopBits", getValue(stopCombo))
            insert("FlowControl", getValue(flowCombo))
        }

        function getValue(id) {
            return id.values[id.currentIndex]
        }

        function settingsToValues() {
            setIndexByValue(baudRateCombo, value("BaudRate"))
            setIndexByValue(dataCombo, value("DataBits"))
            setIndexByValue(parityCombo, value("Parity"))
            setIndexByValue(stopCombo, value("StopBits"))
            setIndexByValue(flowCombo, value("FlowControl"))
        }

        function findIndex(values, v) {
            for(var i=0; i<values.length; i++) {
                if(values[i] === v) return i;
            }
            return -1;
        }

        function setIndexByValue(id, v) {
            id.currentIndex = findIndex(id.values, v)
        }
    }

    Column {
        id: form
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        spacing: 10
        GroupBox {
            title: qsTr("Serial Port Settings")

            Column {
                id: column1
                spacing: 10
                Item {height: 1; width: parent.width }
                ComboBox {
                    id: portCombo
                    model: serialPort.portsMap.keys()
                    width: parent.width
                    onCurrentIndexChanged: {
                        setPortDesc()
                    }
                    onModelChanged: {
                        setPortDesc()
                    }
                    function setPortDesc() {
                        if(currentText) {
                            var v = serialPort.portsMap.value(currentText)
                            if(!v) {
                                v = "N/A";
                            }
                        } else {
                            v = "N/A";
                        }
                        portDesc.description = v;
                    }
                }
                Text {
                    id: portDesc
                    width: parent.width
                    text: "Description: " + description
                    property string description: "N/A"
                    wrapMode: Text.WordWrap
                }
                Grid {
                    columns: 2
                    spacing: 5
                    Label {
                        text: qsTr("Baud Rate:")
                    }
                    ComboBox {
                        id: baudRateCombo
                        model: [ "1200", "2400", "4800", "9600", "19200", "38400", "57600", "115200" ]
                        property var values: [
                            SerialPort.Baud1200, SerialPort.Baud2400,
                            SerialPort.Baud4800, SerialPort.Baud9600,
                            SerialPort.Baud19200, SerialPort.Baud38400,
                            SerialPort.Baud57600, SerialPort.Baud115200,
                        ]
                    }
                    Label {
                        text: qsTr("Data bits:")
                    }
                    ComboBox {
                        id: dataCombo
                        model: [ "5", "6", "7", "8" ]
                        property var values: [
                            SerialPort.Data5, SerialPort.Data6,
                            SerialPort.Data7, SerialPort.Data8,
                        ]
                    }
                    Label {
                        text: qsTr("Parity:")
                    }
                    ComboBox {
                        id: parityCombo
                        model: [ "None", "Even", "Odd", "Space", "Mark" ]
                        property var values: [
                            SerialPort.NoParity, SerialPort.EvenParity,
                            SerialPort.OddParity, SerialPort.SpaceParity,
                            SerialPort.MarkParity,
                        ]
                    }
                    Label {
                        text: qsTr("Stop bits:")
                    }
                    ComboBox {
                        id: stopCombo
                        model: [ "1", "1.5", "2" ]
                        property var values: [
                            SerialPort.OneStop, SerialPort.OneAndHalfStop,
                            SerialPort.TwoStop,
                        ]
                    }
                    Label {
                        text: qsTr("Flow control:")
                    }
                    ComboBox {
                        id: flowCombo
                        model: [ "None", "RTS/CTS", "XON/XOFF" ]
                        property var values: [
                            SerialPort.NoFlowControl, SerialPort.HardwareControl,
                            SerialPort.SoftwareControl,
                        ]
                    }
                }

            }
        }
        Button {
            id: buttonAplly
            text: qsTr("Apply")
            anchors.right: parent.right

            onClicked: {
                root.apply()
//                console.log("Qlist hello:" + serialPort.test.count())
//                for (var i=0; i<serialPort.test.length; i++)
//                    console.log("Array item:", serialPort.test[i])
//                hhh = serialPort.getTest1()
//                console.log("Baud:", baudRateCombo.values[1])
                settingsMap.valuesToSettings()
                root.close()
            }
        }
    }
}

