import './App.css'

// frontend/src/App.jsx
import { useEffect, useState } from "react";
import { getAnalytics } from "./api/fetchData";

function App() {
    const [data, setData] = useState(null);

    useEffect(() => {
        getAnalytics().then(setData);
    }, []);

    if (!data) return <p>Loading...</p>;

    return (
        <div>
            <h1>Analytics</h1>
            <table>
                <thead>
                <td>Title</td>
                <td>Score</td>
                <td>Views</td>
                </thead>
                <tbody>
                {data.map((item, index) => (
                    <tr>
                        <td><h2>{item.movie}</h2></td>
                        <td>{item.score}</td>
                        <td>{item.views}</td>
                    </tr>
                ))}
                </tbody>
            </table>
        </div>
    );
}

export default App;

