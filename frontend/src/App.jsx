import { useEffect, useState } from "react";
import './App.css';
import Row from "./components/Row";


async function fetchEndpoint(url) {
    const res = await fetch(`http://localhost:3001${url}`);
    return res.json();
}

function formatTitle(str) {
    return str
        .replace(/_/g, " ")            // replace underscores with spaces
        .replace(/-/g," ")
        .replace(/\b\w/g, c => c.toUpperCase()); // capitalize each word
}
function DataTable({ title, items, basePath, isShow }) {
    if (!Array.isArray(items) || items.length === 0) {
        return ("");
    }

    return (
        <div>
            <Row
                title={title}
                items={items}
                basePath={basePath}
                isMovie={!isShow}
            />
        </div>
    );
}


function App() {
    const [routes, setRoutes] = useState(null);
    const [data, setData] = useState({});
    const [basePath, setBasePath] = useState("https://image.tmdb.org/t/p/original");

    useEffect(() => {
        fetch("http://localhost:3001/api")
            .then((res) => res.json())
            .then(setRoutes);
    }, []);

    useEffect(() => {
        if (!routes) return;

        const fetchAll = async () => {
            let results = {};
            for (const [path, info] of Object.entries(routes)) {
                const endpointName = info.name;
                results[endpointName] = {};

                for (const [key, val] of Object.entries(info)) {
                    if (val === "name" || val === "both") continue;
                    if (key.startsWith(path)) {
                        const subKey = val; // e.g. "movies", "shows"
                        try {
                            const json = await fetchEndpoint(key);
                            results[endpointName][subKey] = Array.isArray(json) ? json : [];
                        } catch (err) {
                            console.error(`Error fetching ${key}:`, err);
                            results[endpointName][subKey] = [];
                        }
                    }
                }
            }
            setData(results);
        };

        fetchAll();
    }, [routes]);

    if (!routes) return <p>Loading endpoints...</p>;
    if (Object.keys(data).length === 0) return <p>Loading data...</p>;

    return (
        <div>
            <div>
                <nav>
                    <ul>
                        <li>
                            <a href="#">Trakt Plus</a>
                        </li>
                        <li>
                            <a href="#movies">Movies</a>
                        </li>
                        <li>
                            <a href="#shows">Shows</a>
                        </li>
                    </ul>
                </nav>
            </div>
            {Object.entries(data).map(([endpointName, subData]) => (
                <div key={endpointName}>
                    <h1>{formatTitle(endpointName)}</h1>
                    {Object.entries(subData).map(([subKey, items]) => (
                        <DataTable
                            key={subKey}
                            title={subKey}
                            items={items}
                            basePath={basePath}
                            isShow={subKey === "shows"}
                        />
                    ))}
                </div>
            ))}
            <p>Images powered by <a href="https://tmdb.org">TMDB</a></p>
        </div>
    );
}

export default App;
