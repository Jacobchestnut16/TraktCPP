import './App.css'

// frontend/src/App.jsx
import { useEffect, useState } from "react";
import {getPopular, getPosterPathBase, getTopRated} from "./api/fetchData";


function App() {
    const [popData, setPopData] = useState(null);
    const [topData, setTopData] = useState(null);
    const [basePath, setBasePath] = useState(null);

    useEffect(() => {
        getPopular().then(setPopData);
    }, []);
    useEffect(() => {
        getTopRated().then(setTopData);
    }, []);

    useEffect(() =>{
        getPosterPathBase().then(setBasePath)
    },[])

    if (!popData || !topData) return <p>Loading...</p>;

    return (
        <div>
            <h1>Trending</h1>

            <h2>Movies</h2>
            <table border="1" cellPadding="6">
                <thead>
                <tr>
                    <th>Title</th>
                    <th>Year</th>
                    <th>Watchers</th>
                </tr>
                </thead>
                <tbody>
                {popData.movies.map((item, index) => (
                    <tr key={index}>
                        <td>
                            {item.poster_path ? (
                                <img
                                    src={basePath + item.poster_path}
                                    alt={item.title}
                                    width={80}
                                />
                            ) : (
                                <span>No image</span>
                            )}
                        </td>
                        <td>{item.title}</td>
                        <td>{item.release_date}</td>
                        <td>{item.vote_average}</td>
                    </tr>
                ))}
                </tbody>
            </table>

            <h2>Shows</h2>
            <table border="1" cellPadding="6">
                <thead>
                <tr>
                    <th>Title</th>
                    <th>Year</th>
                    <th>Aired Episodes</th>
                    <th>Watchers</th>
                </tr>
                </thead>
                <tbody>
                {popData.shows.map((item, index) => (
                    <tr key={index}>
                        <td>
                            {item.poster_path ? (
                                <img
                                    src={basePath + item.poster_path}
                                    alt={item.title}
                                    width={80}
                                />
                            ) : (
                                <span>No image</span>
                            )}
                        </td>
                        <td>{item.name}</td>
                        <td>{item.first_air_date}</td>
                        <td>{item.vote_average}</td>
                    </tr>
                ))}
                </tbody>
            </table>

            <div>
                <h1>Top Rated</h1>

                <h2>Movies</h2>
                <table border="1" cellPadding="6">
                    <thead>
                    <tr>
                        <th>Title</th>
                        <th>Year</th>
                        <th>Watchers</th>
                    </tr>
                    </thead>
                    <tbody>
                    {topData.movies.map((item, index) => (
                        <tr key={index}>
                            <td>
                                {item.poster_path ? (
                                    <img
                                        src={basePath + item.poster_path}
                                        alt={item.title}
                                        width={80}
                                    />
                                ) : (
                                    <span>No image</span>
                                )}
                            </td>
                            <td>{item.title}</td>
                            <td>{item.release_date}</td>
                            <td>{item.vote_average}</td>
                        </tr>
                    ))}
                    </tbody>
                </table>

                <h2>Shows</h2>
                <table border="1" cellPadding="6">
                    <thead>
                    <tr>
                        <th>Title</th>
                        <th>Year</th>
                        <th>Aired Episodes</th>
                        <th>Watchers</th>
                    </tr>
                    </thead>
                    <tbody>
                    {topData.shows.map((item, index) => (
                        <tr key={index}>
                            <td>
                                {item.poster_path ? (
                                    <img
                                        src={basePath + item.poster_path}
                                        alt={item.title}
                                        width={80}
                                    />
                                ) : (
                                    <span>No image</span>
                                )}
                            </td>
                            <td>{item.name}</td>
                            <td>{item.first_air_date}</td>
                            <td>{item.vote_average}</td>
                        </tr>
                    ))}
                    </tbody>
                </table>
            </div>
        </div>
    );
}

export default App;

