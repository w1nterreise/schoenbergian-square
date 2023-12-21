import Data.Maybe




data Tone = C | CSharp | D | DSharp | E | F | FSharp | G | GSharp | A | ASharp | B deriving (Enum)


instance Show Tone where
    show tone = case tone of
        C  -> "C"
        CSharp -> "C#"
        D  -> "D"
        DSharp -> "D#"
        E  -> "E"
        F  -> "F"
        FSharp -> "F#"
        G  -> "G"
        GSharp -> "G#"
        A  -> "A"
        ASharp -> "A#"
        B  -> "B"


parseString :: String -> Maybe Tone
parseString input = case input of
    "C"    -> Just C
    "C#"   -> Just CSharp
    "D"    -> Just D
    "D#"   -> Just DSharp
    "E"    -> Just E
    "F"    -> Just F
    "F#"   -> Just FSharp
    "G"    -> Just G
    "G#"   -> Just GSharp
    "A"    -> Just A
    "A#"   -> Just ASharp
    "B"    -> Just B
    _       -> Nothing


invertRow :: [Tone] -> [Tone]
invertRow row =
    let firstPitchClass = fromEnum $ head row
        invertedPitches = map (\pitch -> toEnum $ (2 * firstPitchClass - fromEnum pitch) `mod` 12) row
    in invertedPitches


transposeFrom :: Tone -> [Tone] -> [Tone]
transposeFrom interval row = map (\pitch -> toEnum $ (fromEnum pitch + fromEnum interval - fromEnum (head row)) `mod` 12) row


schoenbergianSquare :: [Tone] -> [Tone] -> [[Tone]]
schoenbergianSquare origRow invRow =
    let transposedRows = map (\pitch -> transposeFrom pitch origRow) invRow
    in transposedRows


printLine :: [Tone] -> IO ()
printLine line = do
    mapM_ (\x -> putStr $ (show x) ++ "\t") line
    putStrLn ""




main :: IO ()
main = do
    putStrLn "Original row:"
    s <- getLine
    let row = map (fromJust . parseString) (words s)
    let invertedRow = invertRow row
    let square = schoenbergianSquare row invertedRow
    putStrLn "Schoenbergian square:"
    mapM_ printLine square