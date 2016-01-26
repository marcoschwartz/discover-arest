if (Meteor.isClient) {

  // Events
  Template.home.events({
    'click #on': function() {
      Meteor.call('digitalWrite', "192.168.115.105", 5, 1);
    },
    'click #off': function() {
      Meteor.call('digitalWrite', "192.168.115.105", 5, 0);
    }
  });

  Template.home.rendered = function() {

    // Pin mode
    Meteor.call('pinMode', "192.168.115.105", 5, 'o');

    // Variables
    Meteor.call('variable', "192.168.115.105", 'temperature', function (err, data) {
      $('#temperature').text(data.temperature);
    });

    Meteor.call('variable', "192.168.115.105", 'humidity', function (err, data) {
      $('#humidity').text(data.humidity);
    });

  }

}

if (Meteor.isServer) {

  Meteor.methods({

    digitalWrite: function(ipAddress, pin, state) {
      HTTP.get('http://' + ipAddress + '/digital/' + pin + '/' + state);
    },
    pinMode: function(ipAddress, pin, state) {
      HTTP.get('http://' + ipAddress + '/mode/' + pin + '/' + state);
    },
    variable: function(ipAddress, variable) {
      var answer = HTTP.get('http://' + ipAddress + '/' + variable);
      return answer.data;
    }

  });

}
