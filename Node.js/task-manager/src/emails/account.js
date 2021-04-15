const sgMail = require("@sendgrid/mail")

sgMail.setApiKey(process.env.SENDGRID_API_KEY)

// sgMail.send({
//   to: "phertfelder@gmail.com",
//   from: "phertfelder@me.com",
//   subject: "This is my first email!",
//   text: "I hope this works.",
// })

const sendWelcomeEmail = (email, name) => {
  sgMail.send({
    to: email,
    from: "phertfelder@me.com",
    subject: "Thanks for joining.",
    text: `Welcome to the app, ${name}.`,
  })
}

const sendCancelEmail = (email, name) => {
  sgMail.send({
    to: email,
    from: "phertfelder@me.com",
    subject: "Sorry you want to cancel.",
    text: `Hey ${name}. Goodbye hope to see you back!`,
  })
}
module.exports = {
  sendWelcomeEmail,
  sendCancelEmail,
}
