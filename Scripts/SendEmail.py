import smtplib
import sys
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart

def send_email(receiver_email, code):
    sender_email = "libra.project.admi@gmail.com"
    app_password = "kwcv iybf yisq gtub"

    subject = "Your admin  Verification Code is "
    body = f"Your verification code is: {code}"

    msg = MIMEMultipart()
    msg["From"] = sender_email
    msg["To"] = receiver_email
    msg["Subject"] = subject
    msg.attach(MIMEText(body, "plain"))

    try:
        server = smtplib.SMTP("smtp.gmail.com", 587)
        server.starttls()
        server.login(sender_email, app_password)
        server.sendmail(sender_email, receiver_email, msg.as_string())
        server.quit()
        print("SUCCESS")
    except Exception as e:
        print("ERROR:", e)

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python SendEmail.py <email> <code>")
        sys.exit(1)

    recv = sys.argv[1]
    code = sys.argv[2]
    send_email(recv, code)