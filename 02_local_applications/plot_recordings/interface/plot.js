if (Meteor.isServer) {
  Meteor.startup(function () {
    aREST.addDevice('http', '192.168.115.104');
  });
}

if (Meteor.isClient) {

  // Main route
  Router.route('/', {name: 'home'});

  Template.home.rendered = function() {

    Tracker.autorun(function () {

      // Get all events for temperature
      eventsTemperature = Events.find({variable: 'temperature'}).fetch();
      eventsHumidity = Events.find({variable: 'humidity'}).fetch();

      // Split in arrays
      timestamps = [];
      temperatureData = [];
      humidityData = [];
      for (i = 0; i < eventsTemperature.length; i++){
        timestamps.push(moment(eventsTemperature[i].timestamp).format('HH:mm'));
        temperatureData.push(parseFloat(eventsTemperature[i].value));
        humidityData.push(parseFloat(eventsHumidity[i].value));
      }

      // Set session variables
      Session.set('timestamps', timestamps);
      Session.set('temperatureData', temperatureData);
      Session.set('humidityData', humidityData);

    });

  }

Template.home.temperatureChart = function() {

    return {
        title: {
            text: 'Temperature',
            x: -20 //center
        },
        xAxis: {
            categories: Session.get('timestamps'),
            tickInterval: 10
        },
        yAxis: {
            title: {
                text: 'Temperature (°C)'
            },
            plotLines: [{
                value: 0,
                width: 1,
                color: '#808080'
            }]
        },
        tooltip: {
            valueSuffix: '°C'
        },
        series: [{
            name: 'Temperature',
            data: Session.get('temperatureData')
        }]
    };
};

Template.home.humidityChart = function() {

    return {
        title: {
            text: 'Humidity',
            x: -20 //center
        },
        xAxis: {
            categories: Session.get('timestamps'),
            tickInterval: 10
        },
        yAxis: {
            title: {
                text: 'Humidity (%)'
            },
            plotLines: [{
                value: 0,
                width: 1,
                color: '#808080'
            }]
        },
        tooltip: {
            valueSuffix: '%'
        },
        series: [{
            name: 'Humidity',
            data: Session.get('humidityData')
        }]
    };
};

}
