import React, { useState } from 'react';
import './App.css';

function App() {
  const [buttonClicked, setButtonClicked] = useState('');

  const handleButtonClick = (buttonName) => {
    setButtonClicked(buttonName);
  };

  return (
    <div className="App">
      <header className="App-header">
        <h1>Qt Controller Web Application</h1>
        <div>
          <button className="button" onClick={() => handleButtonClick('Button 1')}>
            Button 1
          </button>
          <button className="button" onClick={() => handleButtonClick('Button 2')}>
            Button 2
          </button>
          <button className="button" onClick={() => handleButtonClick('Button 3')}>
            Button 3
          </button>
          <button className="button" onClick={() => handleButtonClick('Button 4')}>
            Button 4
          </button>
        </div>
        <p>
          {buttonClicked ? `LED ${buttonClicked.split(' ')[1]} is on.` : 'No button pushed.'}
        </p>
      </header>
    </div>
  );
}

export default App;
