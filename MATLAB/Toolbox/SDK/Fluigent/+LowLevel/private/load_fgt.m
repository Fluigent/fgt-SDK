function load_fgt()
%LOAD_FGT Load the Fluigent SDK shared library

global fgt_error_report_mode;

if not(libisloaded('fgt_sdk'))
    
    function_fullname = mfilename('fullpath');
    function_path = strsplit(function_fullname, '\');
    function_directory = strjoin(function_path(1:end-1),'/');
    
    [~,maxArraySize]=computer; 
    is64bitComputer=maxArraySize> 2^31;
    if is64bitComputer
        lib_path = fullfile( function_directory, 'fgt_SDK_64.dll');
        loadlibrary(lib_path,@fgt_SDK_64_prototype, 'alias', 'fgt_sdk');
    else
        lib_path = fullfile( function_directory, 'fgt_SDK_32.dll');
        loadlibrary(lib_path,@fgt_SDK_32_prototype, 'alias', 'fgt_sdk');
    end
    
    fgt_error_report_mode = 'print';
end

end

