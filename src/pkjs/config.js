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
    "type": "toggle",
    "messageKey": "monochrome",
    "label": "Tricolor mode",
    "defaultValue": true
  }, {
    "type": "toggle",
    "messageKey": "invert",
    "label": "Invert Colors",
    "defaultValue": false
  }],
  "capabilities": ["BW"]
}, {
  "type": "section",
  "items": [{
    "type": "heading",
    "defaultValue": "COLORS"
  }, {
    "type": "color",
    "messageKey": "background_color",
    "defaultValue": "000000",
    "label": "Background Color"
  }, {
    "type": "color",
    "messageKey": "number_base_color",
    "defaultValue": "55ffff",
    "label": "Numbers Base Color"
  }, {
    "type": "toggle",
    "messageKey": "number_variation",
    "label": "Number Variation",
    "defaultValue": false
  }, {
    "type": "color",
    "messageKey": "ornament_base_color",
    "defaultValue": "ff55ff",
    "label": "Ornaments Base Color"
  }, {
    "type": "toggle",
    "messageKey": "ornament_variation",
    "label": "Ornament Variation",
    "defaultValue": false
  }],
  "capabilities": ["COLOR"]
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
    "defaultValue": "BOTTOM ROW"
  }, {
    "type": "select",
    "messageKey": "bottomrow",
    "label": "Bottom Row Shows",
    "defaultValue": "0",
    "options": [{
      "label": "Date",
      "value": "0"
    }, {
      "label": "Battery Level",
      "value": "1"
    }]
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
      "value": "4"
    }]
  }]
}, {
  "type": "section",
  "items": [{
    "type": "heading",
    "defaultValue": "ANIMATION"
  }, {
    "type": "toggle",
    "messageKey": "quick_start",
    "label": "Quick Animations",
    "defaultValue": true
  }]
}, {
  "type": "section",
  "items": [{
    "type": "heading",
    "defaultValue": "BATTERY SAVER"
  }, {
    "type": "toggle",
    "messageKey": "battery_saver",
    "label": "Always on Battery Saver",
    "defaultValue": false
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
    "messageKey": "contrast",
    "label": "High Contrast While Charging",
    "defaultValue": false,
    "capabilities": ["COLOR"]
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
