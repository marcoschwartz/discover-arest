if (Meteor.isServer) {
  Meteor.startup(function () {
    aREST.addDevice('http', '192.168.115.104');
  });
}

if (Meteor.isClient) {

  // Main route
  Router.route('/', {name: 'home'});

  Template.home.helpers({

    events: function() {
      return Events.find({}, {sort: {timestamp: -1}});
    }

  });

  // Events
  Template.event.helpers({

    formatDate: function() {
      return moment(this.timestamp).fromNow();
    }

  });

}
