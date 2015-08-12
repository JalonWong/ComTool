import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import io.jalon.SerialPort 1.0
import io.jalon 1.0

ApplicationWindow {
    width: 640
    height: 480
    title: qsTr("Com Tool")
    visible: true
    minimumHeight: 300
    minimumWidth: 400

    Component.onCompleted: {
        closeSerial()
    }

    menuBar: MenuBar {
        Menu {
//            title: qsTr("&File")
//            MenuItem {
//                text: qsTr("&Open")
////                onTriggered: serialPort.start();
////                onTriggered: messageDialog.show(qsTr("Open action triggered"));
//            }
            MenuItem {
                text: qsTr("E&xit")
                onTriggered: Qt.quit();
            }
        }
        Menu {
            title: qsTr("&Calls")
            MenuItem { action: connectAction }
            MenuItem { action: settingsAction }
        }
        Menu {
            title: qsTr("&Operate")
            MenuItem {
                id: menuSend
                text: qsTr("&Send Data")
                onTriggered: sendData()
                enabled: serialPort.isOpen
            }
        }
    }

    toolBar: ToolBar {
        id: mainToolBar
        width: parent.width
        RowLayout {
            anchors.fill: parent
            spacing: 0
            ToolButton { action: connectAction }
            ToolButton { action: settingsAction }
            Item { Layout.fillWidth: true }
        }
    }

    // Action
    Action {
        id: connectAction
        text: qsTr("Connect")
        iconSource: "qrc:/images/disconnect.png"
        checkable: true
        property bool isOpen: serialPort.isOpen
        onIsOpenChanged: {
            if(isOpen) {
                text = qsTr("Disconnect")
                iconSource = "qrc:/images/connect.png"
            } else {
                text = qsTr("Connect")
                iconSource = "qrc:/images/disconnect.png"
            }
        }

        onTriggered: {
            if(isOpen) {
                closeSerial()
            } else {
                openSerial()
            }
            if(checked != isOpen) checked = isOpen;
        }
    }

    Action {
        id: settingsAction
        text: qsTr("Settings")
        iconSource: "qrc:/images/settings.png"
        onTriggered: settingsDialg.show()
    }

    // Main form
    ColumnLayout {
        id: main
        anchors.fill: parent

        TextArea {
            id: textRecv
            anchors.bottom: separator.top
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.left: parent.left
            readOnly: true
        }

        TextArea {
            id: textSend
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.left: parent.left
            textFormat: Text.AutoText
        }

        RowLayout {
            id: separator
            anchors.bottom: textSend.top
            anchors.right: parent.right
            anchors.rightMargin: 5
            anchors.bottomMargin: 2

            Button {
                id: buttonClean
                text: qsTr("Clean")
            }

            Button {
                id: buttonSend
                text: qsTr("Send")
                onClicked: sendData()
                enabled: serialPort.isOpen
            }
        }

        function recvOutput(s) {
            textRecv.insert(textRecv.length,s)
        }

        function getSendData() {
            return textSend.text;
        }
    }    

    // Serial Port
    SerialPort {
        id: serialPort
        onReadyRead: main.recvOutput(readAll());
        property bool isOpen: false
//        onPortsNameChanged: {
//        }
    }

    function sendData() {
        serialPort.writeData(main.getSendData());
    }

    function openSerial() {
        if(serialPort.openSerial()) {
            serialPort.isOpen = true;
        } else {
            messageDialog.warning(serialPort.errorString);
        }
    }

    function closeSerial() {
        serialPort.closeSerial();
        serialPort.isOpen = false;
    }

    // Dialog
    SettingsDialog {
        id: settingsDialg
    }

    MessageDialog {
        id: messageDialog

        function show(caption) {
            messageDialog.text = caption;
            messageDialog.open();
        }

        function information(caption) {
            icon = StandardIcon.Information
            show(caption)
        }

        function warning(caption) {
            icon = StandardIcon.Warning
            show(caption)
        }
    }
}
