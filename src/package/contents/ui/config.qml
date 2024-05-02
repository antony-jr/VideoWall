import QtMultimedia
import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts
import org.kde.kirigami as Kirigami
import org.kde.kirigami as Kirigami

Kirigami.FormLayout {
    id: root

    property alias formLayout: root // required by parent
    property string cfg_VideoOrImage
    property string cfg_Folder
    property int cfg_Fill
    property double cfg_Volume
    property double cfg_Rate

    twinFormLayouts: parentLayout // required by parent

    FileDialog {
        id: fileDialog

        title: "Pick a Video/Image file"
        nameFilters: ["Video Files (*.mp4 *.ogv *.ogg *.avi *.mpg *.mpeg *.wmv *.mov *.webm *.flv *.mkv *.matroska)", "Image Files (*.png *.jpeg *.jpg)"]
        onAccepted: {
            cfg_VideoOrImage = fileDialog.selectedFiles[0];
            cfg_Folder = fileDialog.currentFolder;
        }
    }

    RowLayout {
        TextField {
            placeholderText: qsTr("Set Video or Image")
            text: cfg_VideoOrImage.toString().replace(/^file:\/\//, '')
            readOnly: true
        }

        Button {
            id: dialogButton

            icon.name: "folder-videos-symbolic"
            text: i18nd("@button:toggle_show_videos", "Set Source Image/Video")
            onClicked: {
                fileDialog.open();
            }
        }

    }

    RowLayout {
        Label {
            horizontalAlignment: Text.AlignRight
            text: i18n("Positioning:")
        }

        ComboBox {
            currentIndex: cfg_Fill
            model: ["Stretch", "Preserve Aspect, Fit", "Preserve Aspect, Crop"]
            onCurrentIndexChanged: function(currentIndex) {
                cfg_Fill = currentIndex;
            }
        }

    }

    RowLayout {
        Label {
            horizontalAlignment: Text.AlignRight
            text: i18n("Playback Rate:")
        }

        Slider {
            id: rateSlider

            from: 0
            value: cfg_Rate
            to: 4
            onMoved: {
                cfg_Rate = rateSlider.value;
            }
        }

        Label {
            id: rateLabel

            text: i18n(Number(cfg_Rate).toLocaleString(Qt.locale(), "f", 1) + "x")
        }

    }

    RowLayout {
        Label {
            horizontalAlignment: Text.AlignRight
            text: i18n("Volume:")
        }

        Slider {
            id: volSlider

            from: 0
            value: cfg_Volume
            to: 2
            onMoved: {
                cfg_Volume = volSlider.value;
            }
        }

        Label {
            id: volumeLabel

            text: i18n(Number(cfg_Volume).toLocaleString(Qt.locale(), "f", 2))
        }

    }

}
