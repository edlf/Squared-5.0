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
    "label": "Monochrome",
    "defaultValue": false
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
    "type": "radiogroup",
    "messageKey": "number_base_color",
    "label": "Numbers",
    "defaultValue": "0",
    "options": [{
      "label": "White",
      "value": 0
    }, {
      "label": "Diamond",
      "value": 0
    }, {
      "label": "Ruby",
      "value": 0
    }, {
      "label": "Fire",
      "value": 0
    }, {
      "label": "Forest",
      "value": 0
    }, {
      "label": "Quartz",
      "value": 0
    }, {
      "label": "Red",
      "value": 0
    }, {
      "label": "Green",
      "value": 0
    }, {
      "label": "Blue",
      "value": 0
    }, {
      "label": "Yellow",
      "value": 0
    }, {
      "label": "Cyan",
      "value": 0
    }, {
      "label": "Magenta",
      "value": 0
    }, {
      "label": "Violet",
      "value": 0
    }, {
      "label": "Orange",
      "value": 0
    }, {
      "label": "Vivid Cerulean",
      "value": 0
    }, {
      "label": "Chrome Yellow",
      "value": 0
    }, {
      "label": "Spring Green",
      "value": 0
    }, {
      "label": "Black",
      "value": 0
    }, {
      "label": "Dark Gray",
      "value": 0
    }, {
      "label": "Light Gray",
      "value": 0
    }]
  }, {
    "type": "radiogroup",
    "messageKey": "ornament_base_color",
    "label": "Ornaments",
    "defaultValue": "0",
    "options": [{
      "label": "Black",
      "value": 0
    }, {
      "label": "White",
      "value": 0
    }, {
      "label": "Dark Gray",
      "value": 0
    }, {
      "label": "Light Gray",
      "value": 0
    }, {
      "label": "Red",
      "value": 0
    }, {
      "label": "Green",
      "value": 0
    }, {
      "label": "Blue",
      "value": 0
    }, {
      "label": "Yellow",
      "value": 0
    }, {
      "label": "Cyan",
      "value": 0
    }, {
      "label": "Magenta",
      "value": 0
    }, {
      "label": "Violet",
      "value": 0
    }, {
      "label": "Orange",
      "value": 0
    }, {
      "label": "Vivid Cerulean",
      "value": 0
    }, {
      "label": "Chrome Yellow",
      "value": 0
    }, {
      "label": "Spring Green",
      "value": 0
    }]
  }, {
    "type": "radiogroup",
    "messageKey": "background_color",
    "label": "Background",
    "defaultValue": 0,
    "options": [{
      "label": "Black",
      "value": 0
    }, {
      "label": "White",
      "value": 0
    }, {
      "label": "Dark Gray",
      "value": 0
    }, {
      "label": "Light Gray",
      "value": 0
    }, {
      "label": "Red",
      "value": 0
    }, {
      "label": "Green",
      "value": 0
    }, {
      "label": "Blue",
      "value": 0
    }, {
      "label": "Yellow",
      "value": 0
    }, {
      "label": "Cyan",
      "value": 0
    }, {
      "label": "Magenta",
      "value": 0
    }, {
      "label": "Violet",
      "value": 0
    }, {
      "label": "Orange",
      "value": 0
    }, {
      "label": "Vivid Cerulean",
      "value": 0
    }, {
      "label": "Chrome Yellow",
      "value": 0
    }, {
      "label": "Spring Green",
      "value": 0
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
    "type": "radiogroup",
    "messageKey": "bottomrow",
    "label": "Bottom Row Shows",
    "defaultValue": 0,
    "options": [{
      "label": "Date",
      "value": 0
    }, {
      "label": "Battery Level",
      "value": 1
    }, {
      "label": "Step Goal",
      "value": 2,
      "capabilities": ["HEALTH"]
    }, {
      "label": "Heart Rate",
      "value": 3,
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
    "type": "radiogroup",
    "messageKey": "wristflick",
    "label": "Flick of the Wrist Shows",
    "defaultValue": 0,
    "options": [{
      "label": "Nothing",
      "value": 0
    }, {
      "label": "Battery Level",
      "value": 1
    }, {
      "label": "Step Goal",
      "value": 2,
      "capabilities": ["HEALTH"]
    }, {
      "label": "Heart Rate + Zone",
      "value": 3,
      "capabilities": ["HEALTH"]
    }, {
      "label": "Big Date",
      "value": 4
    }]
  }]
}, {
  "type": "section",
  "items": [{
    "type": "heading",
    "defaultValue": "DAILY STEP GOAL"
  }, {
    "type": "text",
    "label": "Squared gets your steps from Pebble Health"
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
    "messageKey": "nightsaver",
    "label": "Battery Saver",
    "defaultValue": false
  }, {
    "type": "radiogroup",
    "messageKey": "ns_start",
    "label": "Stop Animations at",
    "defaultValue": 4,
    "options": [{
      "label": "2:00 pm",
      "value": 0
    }, {
      "label": "4:00 pm",
      "value": 1
    }, {
      "label": "6:00 pm",
      "value": 2
    }, {
      "label": "8:00 pm",
      "value": 3
    }, {
      "label": "10:00 pm",
      "value": 4
    }, {
      "label": "Midnight",
      "value": 5
    }, {
      "label": "2:00 am",
      "value": 6
    }, {
      "label": "4:00 am",
      "value": 7
    }, {
      "label": "6:00 am",
      "value": 8
    }, {
      "label": "8:00 am",
      "value": 9
    }, {
      "label": "10:00 am",
      "value": 10
    }, {
      "label": "Noon",
      "value": 11
    }]
  }, {
    "type": "radiogroup",
    "messageKey": "ns_stop",
    "label": "Continue Animations at",
    "defaultValue": 9,
    "options": [{
      "label": "2:00 pm",
      "value": 0
    }, {
      "label": "4:00 pm",
      "value": 1
    }, {
      "label": "6:00 pm",
      "value": 2
    }, {
      "label": "8:00 pm",
      "value": 3
    }, {
      "label": "10:00 pm",
      "value": 4
    }, {
      "label": "Midnight",
      "value": 5
    }, {
      "label": "2:00 am",
      "value": 6
    }, {
      "label": "4:00 am",
      "value": 7
    }, {
      "label": "6:00 am",
      "value": 8
    }, {
      "label": "8:00 am",
      "value": 9
    }, {
      "label": "10:00 am",
      "value": 10
    }, {
      "label": "Noon",
      "value": 11
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
