module.exports = [{
  "type": "heading",
  "id": "main-heading",
  "defaultValue": "Squared Config",
  "size": 1
}, {
  "type": "section",
  "items": [{
    "type": "heading",
    "defaultValue": "COLORS"
  }, {
    "type": "color",
    "messageKey": "background_color",
    "defaultValue": "000000",
    "allowGray": true,
    "label": "Background Color"
  }, {
    "type": "color",
    "messageKey": "number_base_color",
    "defaultValue": "55ffff",
    "allowGray": true,
    "label": "Numbers Base Color"
  }, {
    "type": "color",
    "messageKey": "ornament_base_color",
    "defaultValue": "ff55ff",
    "allowGray": true,
    "label": "Ornaments Base Color"
  }]
}, {
  "type": "section",
  "items": [{
    "type": "heading",
    "defaultValue": "APPEARANCE"
  }, {
    "type": "toggle",
    "messageKey": "leading_zero",
    "label": "Leading Zeros",
    "defaultValue": false
  }]
}, {
  "type": "section",
  "items": [{
    "type": "heading",
    "defaultValue": "DATE"
  }, {
    "type": "toggle",
    "messageKey": "eu_date",
    "label": "European Date (dd/mm)",
    "defaultValue": true
  }, {
    "type": "toggle",
    "messageKey": "center",
    "label": "Ceneter-Align Date",
    "defaultValue": false
  }, {
    "type": "toggle",
    "messageKey": "weekday",
    "label": "Replace Month with Weekday",
    "defaultValue": false
  }]
}, {
  "type": "section",
  "items": [{
    "type": "heading",
    "defaultValue": "WRIST FLICK"
  }, {
    "type": "select",
    "messageKey": "wristflick",
    "label": "Flick of the Wrist Shows",
    "defaultValue": "0",
    "options": [{
      "label": "Nothing",
      "value": "0"
    }, {
      "label": "Battery Level",
      "value": "1"
    }, {
      "label": "Big Date",
      "value": "2"
    }]
  }]
}, {
  "type": "section",
  "items": [{
    "type": "heading",
    "defaultValue": "BATTERY SAVER"
  }, {
    "type": "toggle",
    "messageKey": "nightsaver",
    "label": "Scheduled Battery Saver",
    "defaultValue": true
  }, {
    "type": "select",
    "messageKey": "ns_start",
    "label": "Stop Animations at",
    "defaultValue": "4",
    "options": [{
      "label": "2:00 pm",
      "value": "0"
    }, {
      "label": "4:00 pm",
      "value": "1"
    }, {
      "label": "6:00 pm",
      "value": "2"
    }, {
      "label": "8:00 pm",
      "value": "3"
    }, {
      "label": "10:00 pm",
      "value": "4"
    }, {
      "label": "Midnight",
      "value": "5"
    }, {
      "label": "2:00 am",
      "value": "6"
    }, {
      "label": "4:00 am",
      "value": "7"
    }, {
      "label": "6:00 am",
      "value": "8"
    }, {
      "label": "8:00 am",
      "value": "9"
    }, {
      "label": "10:00 am",
      "value": "10"
    }, {
      "label": "Noon",
      "value": "11"
    }]
  }, {
    "type": "select",
    "messageKey": "ns_stop",
    "label": "Continue Animations at",
    "defaultValue": "9",
    "options": [{
      "label": "2:00 pm",
      "value": "0"
    }, {
      "label": "4:00 pm",
      "value": "1"
    }, {
      "label": "6:00 pm",
      "value": "2"
    }, {
      "label": "8:00 pm",
      "value": "3"
    }, {
      "label": "10:00 pm",
      "value": "4"
    }, {
      "label": "Midnight",
      "value": "5"
    }, {
      "label": "2:00 am",
      "value": "6"
    }, {
      "label": "4:00 am",
      "value": "7"
    }, {
      "label": "6:00 am",
      "value": "8"
    }, {
      "label": "8:00 am",
      "value": "9"
    }, {
      "label": "10:00 am",
      "value": "10"
    }, {
      "label": "Noon",
      "value": "11"
    }]
  }]
}, {
  "type": "section",
  "items": [{
    "type": "heading",
    "defaultValue": "ADVANCED"
  }, {
    "type": "toggle",
    "messageKey": "btvibe",
    "label": "Vibrate on Disconnect",
    "defaultValue": true
  }, {
    "type": "toggle",
    "messageKey": "backlight",
    "label": "Backlight on While Charging",
    "defaultValue": false
  }]
}, {
  "type": "submit",
  "defaultValue": "SEND"
}]
