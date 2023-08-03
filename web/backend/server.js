const express = require('express');
const app = express();
const port = 5000;
const { exec } = require('child_process'); // Import child_process

app.use(express.json()); // Parse JSON body

app.post('/trigger-qt', (req, res) => {
  const { buttonId } = req.body;
  
  // Execute shell command to interact with Qt application
  exec(`your-qt-application-command ${buttonId}`, (error, stdout, stderr) => {
    if (error) {
      console.error(`Error: ${error.message}`);
      return res.status(500).send('Error occurred.');
    }
    console.log(`Qt application response: ${stdout}`);
    res.send('Signal sent to Qt application.');
  });
});

app.listen(port, () => {
  console.log(`Server is running on port ${port}`);
});
