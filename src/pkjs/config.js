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
    "defaultValue": "COLOR PRESETS"
  }, {
    "type": "text",
    "defaultValue": "Overrides above color settings"
  }, {
    "type": "toggle",
    "messageKey": "use_presets",
    "label": "Use presets",
    "defaultValue": true
  }, {
    "type": "select",
    "messageKey": "numbers_preset",
    "label": "Numbers",
    "defaultValue": "1",
    "options": [{
      "label": "White",
      "value": "0"
    }, {
      "label": "Diamond",
      "value": "1"
    }, {
      "label": "Ruby",
      "value": "2"
    }, {
      "label": "Fire",
      "value": "3"
    }, {
      "label": "Forest",
      "value": "4"
    }, {
      "label": "Quartz",
      "value": "5"
    }, {
      "label": "Red",
      "value": "6"
    }, {
      "label": "Green",
      "value": "7"
    }, {
      "label": "Blue",
      "value": "8"
    }, {
      "label": "Yellow",
      "value": "9"
    }, {
      "label": "Cyan",
      "value": "10"
    }, {
      "label": "Magenta",
      "value": "11"
    }, {
      "label": "Violet",
      "value": "12"
    }, {
      "label": "Orange",
      "value": "13"
    }, {
      "label": "Vivid Cerulean",
      "value": "14"
    }, {
      "label": "Chrome Yellow",
      "value": "15"
    }, {
      "label": "Spring Green",
      "value": "16"
    }, {
      "label": "Black",
      "value": "17"
    }, {
      "label": "Dark Gray",
      "value": "18"
    }, {
      "label": "Light Gray",
      "value": "19"
    }]
  }, {
    "type": "select",
    "messageKey": "ornaments_preset",
    "label": "Ornaments",
    "defaultValue": "2",
    "options": [{
      "label": "White",
      "value": "0"
    }, {
      "label": "Diamond",
      "value": "1"
    }, {
      "label": "Ruby",
      "value": "2"
    }, {
      "label": "Fire",
      "value": "3"
    }, {
      "label": "Forest",
      "value": "4"
    }, {
      "label": "Quartz",
      "value": "5"
    }, {
      "label": "Red",
      "value": "6"
    }, {
      "label": "Green",
      "value": "7"
    }, {
      "label": "Blue",
      "value": "8"
    }, {
      "label": "Yellow",
      "value": "9"
    }, {
      "label": "Cyan",
      "value": "10"
    }, {
      "label": "Magenta",
      "value": "11"
    }, {
      "label": "Violet",
      "value": "12"
    }, {
      "label": "Orange",
      "value": "13"
    }, {
      "label": "Vivid Cerulean",
      "value": "14"
    }, {
      "label": "Chrome Yellow",
      "value": "15"
    }, {
      "label": "Spring Green",
      "value": "16"
    }, {
      "label": "Black",
      "value": "17"
    }, {
      "label": "Dark Gray",
      "value": "18"
    }, {
      "label": "Light Gray",
      "value": "19"
    }]
  }, {
    "type": "select",
    "messageKey": "bg_preset",
    "label": "Background",
    "defaultValue": "0",
    "options": [{
      "label": "Black",
      "value": "0"
    }, {
      "label": "White",
      "value": "1"
    }, {
      "label": "Dark Gray",
      "value": "2"
    }, {
      "label": "Light Gray",
      "value": "3"
    }, {
      "label": "Red",
      "value": "4"
    }, {
      "label": "Green",
      "value": "5"
    }, {
      "label": "Blue",
      "value": "6"
    }, {
      "label": "Yellow",
      "value": "7"
    }, {
      "label": "Cyan",
      "value": "8"
    }, {
      "label": "Magenta",
      "value": "9"
    }, {
      "label": "Violet",
      "value": "10"
    }, {
      "label": "Orange",
      "value": "11"
    }, {
      "label": "Vivid Cerulean",
      "value": "12"
    }, {
      "label": "Chrome Yellow",
      "value": "13"
    }, {
      "label": "Spring Green",
      "value": "14"
    }]
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
  }, {
    "type": "toggle",
    "messageKey": "large_mode",
    "label": "Large Numbers",
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
    }, {
      "label": "Step Goal",
      "value": "2",
      "capabilities": ["HEALTH"]
    }, {
      "label": "Heart Rate",
      "value": "3",
      "capabilities": ["HEALTH"]
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
      "label": "Step Goal",
      "value": "2",
      "capabilities": ["HEALTH"]
    }, {
      "label": "Heart Rate + Zone",
      "value": "3",
      "capabilities": ["HEALTH"]
    }, {
      "label": "Big Date",
      "value": "4"
    }]
  }]
}, {
  "type": "section",
  "items": [{
    "type": "heading",
    "defaultValue": "DAILY STEP GOAL"
  }, {
    "type": "text",
    "defaultValue": "Squared gets your steps from Pebble Health"
  }, {
    "type": "toggle",
    "messageKey": "dynamicstepgoal",
    "label": "Dynamic Step Goal",
    "defaultValue": false
  }, {
    "type": "slider",
    "messageKey": "stepgoal",
    "label": "Step Goal",
    "min": 1000,
    "max": 25000,
    "step": 1000,
    "defaultValue": 10000
  }, {
    "type": "toggle",
    "messageKey": "cheeky",
    "label": "Cheeky Quips & Encouragement",
    "defaultValue": false
  }],
  "capabilities": ["HEALTH"]
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
