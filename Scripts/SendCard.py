import smtplib
import sys
import os
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from email.mime.image import MIMEImage


SENDER_EMAIL = "libra.project.admi@gmail.com"
SENDER_PASSWORD = "kwcv iybf yisq gtub" # Same one used for OTP
IMAGE_PATH = r"D:/Libra/Assets/LibraCard.png"

def send_card(user_email):
    # Check 1 for seeing if image is there or nah
    if not os.path.exists(IMAGE_PATH):
        print(f"Error: Image not found at {IMAGE_PATH}")
        return

    try:
        # create email obj
        msg = MIMEMultipart()
        msg['Subject'] = "Thank You for Voting.  - Libra System" # the subject line
        msg['From'] = SENDER_EMAIL
        msg['To'] = user_email

        # Adding the text
        text = MIMEText("Thank you for voting. Consider the below attachment as a small token of gratitude", 'plain')
        msg.attach(text)

        # attachment which is the image of card
        with open(IMAGE_PATH, 'rb') as f:
            img_data = f.read()
            # seeing image type i.e png or jpg
            img_type = IMAGE_PATH.split('.')[-1]
            image = MIMEImage(img_data, name=os.path.basename(IMAGE_PATH), _subtype=img_type)
            msg.attach(image)

        # Sending
        server = smtplib.SMTP('smtp.gmail.com', 587)
        server.starttls()
        server.login(SENDER_EMAIL, SENDER_PASSWORD)
        server.sendmail(SENDER_EMAIL, user_email, msg.as_string())
        server.quit()

        print("Card sent successfully!")

    except Exception as e:
        print(f"Failed to send email: {e}")

if __name__ == "__main__":
    if len(sys.argv) > 1:
        email_arg = sys.argv[1]
        send_card(email_arg)
    else:
        print("No email provided.")